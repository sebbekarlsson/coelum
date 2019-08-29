#ifndef COELUM_SOUND_H
#define COELUM_SOUND_H
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/alc.h>
#endif


typedef struct AL_STRUCT
{
    const char* defname;
    ALCdevice *device;
    ALCcontext *context;
} AL_T;

typedef struct SOUND_STRUCT
{
    unsigned frequency;
    float seconds;
    char* fname;
    AL_T* al;
} sound_T;

AL_T* init_al();

void al_free(AL_T* al);

void play_sound_threaded(unsigned frequency, float seconds, AL_T* al);

void play_sound_wav_threaded(char* fname, AL_T* al);

void* play_sound(void* s);

void* play_sound_wav(void* s);
#endif
