#ifndef PONG_ACTOR_BALL_H
#define PONG_ACTOR_BALL_H
#include "actor.h"


typedef struct ACTOR_BALL_STRUCT {
    actor base;
    float target_angle;
} actor_ball;


actor_ball* init_actor_ball(float x, float y, float z);

void actor_ball_tick(actor* self);

void actor_ball_draw(actor* self);
#endif
