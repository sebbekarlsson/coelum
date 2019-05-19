#ifndef COELUM_SOUND_H
#define COELUM_SOUND_H

typedef struct SOUND_STRUCT {
    unsigned frequency;
    float seconds;
} sound;

void init_al();
void exit_al();
void play_sound_threaded(unsigned frequency, float seconds);
void* play_sound(void* s);
#endif
