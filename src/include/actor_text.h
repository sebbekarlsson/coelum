#ifndef PONG_ACTOR_TEXT_H
#define PONG_ACTOR_TEXT_H
#include "actor.h"

typedef struct ACTOR_TEXT_STRUCT {
    actor base;
    char* text;
} actor_text;


actor_text* init_actor_text(float x, float y, float z, char* text);

void actor_text_tick(actor* self);

void actor_text_draw(actor* self);
#endif
