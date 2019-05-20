#ifndef COELUM_ACTOR_H
#define COELUM_ACTOR_H
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct ACTOR_STRUCT {
    int type; // used to separate actors from one and other
    float x;
    float y;
    float z;
    float dx;
    float dy;
    float dz;
    float friction;
    int width;
    int height;
    int depth;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int shader_program;
    unsigned int texture;
    int loaded;
    mat4 model;
    void (*tick)(void* self);
    void (*draw)(void* self);
    void (*load)(void* self);
} actor_T;

actor_T* init_actor(float x, float y, float z);

actor_T* actor_constructor(
    actor_T* a,
    float x,
    float y,
    float z,
    void (*tick)(actor_T* self),
    void (*draw)(actor_T* self)
);

void actor_tick(actor_T* a);

void actor_draw(actor_T* a);

void actor_push(actor_T* self, float angle, float acceleration);
#endif
