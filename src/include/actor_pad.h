#ifndef PONG_ACTOR_PAD_H
#define PONG_ACTOR_PAD_H
#include "actor.h"


typedef struct ACTOR_PAD_STRUCT {
    actor base;
    float speed;
    int player;
    float target_x;
    float target_y;
    int target_y_error;
    int use_error;
} actor_pad;


actor_pad* init_actor_pad(float x, float y, float z, int player);

void actor_pad_tick(actor* self);

void actor_pad_draw(actor* self);
#endif
