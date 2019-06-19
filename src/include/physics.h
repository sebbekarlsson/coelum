#ifndef COELUM_PHYSICS_H
#define COELUM_PHYSICS_H
#include "actor.h"


void physics_to_zero(float* value, float friction);

void physics_tick_actor(actor_T* actor);

void physics_vec2_push(float* x, float* y, float angle, float length);
#endif
