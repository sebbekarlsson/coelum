#ifndef COELUM_ACTOR_LIGHT_H
#define COELUM_ACTOR_LIGHT_H
#include "actor.h"


typedef struct ACTOR_LIGHT_STRUCT
{
    actor_T base;
    float intensity;
} actor_light_T;

actor_light_T* init_actor_light(float x, float y, float z, float intensity);

void actor_light_tick(actor_T* self);

void actor_light_draw(actor_T* self);
#endif
