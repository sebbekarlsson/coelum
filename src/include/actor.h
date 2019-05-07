#ifndef PONG_ACTOR_H
#define PONG_ACTOR_H
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct ACTOR_STRUCT {
    int type;
    float x;
    float y;
    float z;
    float dx;
    float dy;
    float dz;
    float friction;
    int width;
    int height;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture;
    int loaded;
    mat4 model;
    void (*tick)(void* self);
    void (*draw)(void* self);
    void (*load)(void* self);
    // void (*unload)(void* self);
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

void actor_push(actor* self, float degree, float acceleration);
#endif
