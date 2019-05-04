#ifndef PONG_ACTOR_H
#define PONG_ACTOR_H
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct ACTOR_STRUCT {
    float x;
    float y;
    float z;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture;
    mat4 model;
    void (*tick)(void* self);
    void (*draw)(void* self);
} actor;

actor* init_actor(float x, float y, float z);

actor* actor_constructor(
    actor* a,
    float x,
    float y,
    float z,
    void (*tick)(actor* self),
    void (*draw)(actor* self)
);

void actor_tick(actor* a);

void actor_draw(actor* a);
#endif
