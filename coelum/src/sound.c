#include "include/sound.h"
#include <cglm/types.h>
#include <AL/al.h>
#include <AL/alut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <audio/wave.h>


/**
 * Initialize OpenAL
 * 
 * @return AL_T*
 */
AL_T* init_al()
{
    AL_T* al = calloc(1, sizeof(struct AL_STRUCT));

    al->defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    printf("Default sound device: %s\n", al->defname);

    al->device = alcOpenDevice(al->defname);
    if (!al->device)
        printf("Could not setup sound device %s\n", al->defname);

    al->context = alcCreateContext(al->device, NULL);
    if (!alcMakeContextCurrent(al->context))
        printf("Could not make sound context\n"); 

    ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

    alListener3f(AL_POSITION, 0, 0, 1.0f);
    // check for errors
    alListener3f(AL_VELOCITY, 0, 0, 0);
    // check for errors
    alListenerfv(AL_ORIENTATION, listenerOri);
    // check for errors
    
    return al;
}

/**
 * Cleanup OpenAL
 */
void al_free(AL_T* al)
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(al->context);
    alcCloseDevice(al->device);

    free(al);
}

/**
 * Play a frequency in a new thread
 *
 * @param unsigned frequency
 * @param float seconds
 */
void play_sound_threaded(unsigned frequency, float seconds, AL_T* al)
{
    sound_T* s = calloc(1, sizeof(struct SOUND_STRUCT));
    s->frequency = frequency;
    s->seconds = seconds;
    s->al = al;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, play_sound, s);
}

/**
 * Play a wav in a new thread
 *
 * @param unsigned frequency
 * @param float seconds
 */
void play_sound_wav_threaded(char* fname, AL_T* al)
{
    sound_T* s = calloc(1, sizeof(struct SOUND_STRUCT));
    s->fname = fname;
    s->al = al;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, play_sound_wav, s);
}

/**
 * No body should call this function, it is used in `play_sound_threaded`.
 *
 * @parma void* s
 */
void* play_sound(void* s)
{
    sound_T* sound = (sound_T*) s;
    unsigned frequency = sound->frequency;
    float seconds = sound->seconds;

    /* Create buffer to store samples */
    ALuint buf;
    alGenBuffers(1, &buf);

    /* Fill buffer with Sine-Wave */
    unsigned sample_rate = 22050;
    size_t buf_size = seconds * sample_rate;

    short *samples = calloc(buf_size, sizeof(short));

    for(int i=0; i<buf_size; ++i)
        samples[i] = 32760 * sin((2.f * GLM_PI * frequency) / sample_rate * i);

    alBufferData(buf, AL_FORMAT_MONO16, samples, buf_size, sample_rate);

    /* Set-up sound source and play buffer */
    ALuint src = 0;
    alGenSources(1, &src);
    alSourcei(src, AL_BUFFER, buf);
    alSourcePlay(src);

    /* While sound is playing, sleep */
    sleep(seconds);

    free(samples);
    free(sound);

    return (void*) 0;
}


static inline ALenum to_al_format(short channels, short samples)
{
    unsigned int stereo = (channels > 1);

    switch (samples) {
        case 16:
            if (stereo)
                return AL_FORMAT_STEREO16;
            else
                return AL_FORMAT_MONO16;
        case 8:
            if (stereo)
                return AL_FORMAT_STEREO8;
            else
                return AL_FORMAT_MONO8;
        default:
            return -1;
    }
}

/**
 * No one should call this function except `play_sound_wav_threaded`
 *
 * @param void* s
 */
void* play_sound_wav(void* s)
{
    sound_T* sound = (sound_T*) s;

    if (!sound->fname)
        printf("No fname in sound\n");

    if (!alcMakeContextCurrent(sound->al->context))
        printf("Could not make sound context\n");

    ALuint source;

    alGenSources((ALuint)1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);

    ALuint buffer;

    alGenBuffers((ALuint)1, &buffer);

    WaveInfo *wave;
    char *bufferData;
    int ret;

    wave = WaveOpenFileForReading(sound->fname);
    if (!wave) {
        fprintf(stderr, "failed to read wave file\n");
        exit(1);
    }

    ret = WaveSeekFile(0, wave);
    if (ret) {
        fprintf(stderr, "failed to seek wave file\n");
        exit(1);
    }

    bufferData = malloc(wave->dataSize);
    if (!bufferData) {
        perror("malloc");
        exit(1);
    }

    ret = WaveReadFile(bufferData, wave->dataSize, wave);
    if (ret != wave->dataSize) {
        fprintf(stderr, "short read: %d, want: %d\n", ret, wave->dataSize);
        exit(1);
    }

    alBufferData(buffer, to_al_format(wave->channels, wave->bitsPerSample),
            bufferData, wave->dataSize, wave->sampleRate);

    alSourcei(source, AL_BUFFER, buffer);

    alSourcePlay(source);

    ALint source_state;
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);

    while (source_state == AL_PLAYING)
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    free(sound);
}
