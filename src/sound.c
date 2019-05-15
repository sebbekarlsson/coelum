#include "include/sound.h"
#include <AL/al.h>
#include <AL/alut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <AL/alc.h>
#include <unistd.h>
#include <pthread.h>


void init_al()
{
    ALCdevice *dev = NULL;
    ALCcontext *ctx = NULL;

    const char *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    printf("Default sound device: %s\n", defname);

    dev = alcOpenDevice(defname);
    ctx = alcCreateContext(dev, NULL);
    alcMakeContextCurrent(ctx);
}

void exit_al()
{
    ALCdevice *dev = NULL;
    ALCcontext *ctx = NULL;
    ctx = alcGetCurrentContext();
    dev = alcGetContextsDevice(ctx);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
}

void play_sound_threaded(unsigned frequency, float seconds)
{
    sound* s = calloc(1, sizeof(struct SOUND_STRUCT));
    s->frequency = frequency;
    s->seconds = seconds;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, play_sound, s);
    //pthread_join(thread_id, NULL);    
}

void* play_sound(void* s)
{
    sound* snd = (sound*) s;
    unsigned frequency = snd->frequency;
    float seconds = snd->seconds;

    /* initialize OpenAL */
    //init_al();

    /* Create buffer to store samples */
    ALuint buf;
    alGenBuffers(1, &buf);
    //al_check_error();

    /* Fill buffer with Sine-Wave */
    unsigned sample_rate = 22050;
    size_t buf_size = seconds * sample_rate;

    short *samples = calloc(buf_size, sizeof(short));
    for(int i=0; i<buf_size; ++i)
    {
        samples[i] = 32760 * sin((2.f * M_PI * frequency) / sample_rate * i);
    }

    alBufferData(buf, AL_FORMAT_MONO16, samples, buf_size, sample_rate);
    //al_check_error();

    /* Set-up sound source and play buffer */
    ALuint src = 0;
    alGenSources(1, &src);
    alSourcei(src, AL_BUFFER, buf);
    alSourcePlay(src);

    /* While sound is playing, sleep */
    //al_check_error();
    sleep(seconds);

    /* Dealloc OpenAL */
    //exit_al();
    //al_check_error();
    free(samples);
    free(snd);

    return (void*) 0;
}
