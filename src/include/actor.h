#ifndef PONG_ACTOR_H
#define PONG_ACTOR_H
typedef struct ACTOR_STRUCT {
    float x;
    float y;
    float z;
} actor;

actor* init_actor(float x, float y, float z);

void tick_actor(actor* a);

void draw_actor(actor* a);
#endif
