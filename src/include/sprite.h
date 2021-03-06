#ifndef COELUM_SPRITE_H
#define COELUM_SPRITE_H
#include "dynamic_list.h"
#include "state.h"
#include <sys/time.h>


typedef struct SPRITE_STRUCT
{
    dynamic_list_T* textures;
    float width;
    float height;
    float r;
    float g;
    float b;
    float a;
    float frame_delay;  // time spent on every frame
    struct timeval timer;
    unsigned int index;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int animate;
} sprite_T;

sprite_T* init_sprite(dynamic_list_T* textures, float frame_delay, float width, float height);

sprite_T* init_sprite_from_file(const char* filename, int mode, float frame_delay, float width, float height);

void sprite_draw(sprite_T* sprite, state_T* state);

void sprite_free(sprite_T* sprite);
#endif
