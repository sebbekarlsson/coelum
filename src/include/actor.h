#ifndef COELUM_ACTOR_H
#define COELUM_ACTOR_H
#include <cglm/cglm.h>
#include <cglm/call.h>
#include "sprite.h"


typedef struct ACTOR_STRUCT
{
    const char* type_name;  // used to separate actors from one and other.
    float x;
    float y;
    float z;
    float dx;  // delta x
    float dy;  // delta y
    float dz;  // delta z
    float rx;  // rotation
    float ry;  // rotation
    float rz;  // rotation
    float offset_x;
    float offset_y;
    float offset_z;
    float friction;
    int width;
    int height;
    int depth;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int shader_program;
    unsigned int use_offset;
    unsigned int reverse;
    int loaded;
    mat4 model;
    sprite_T* sprite;
    void (*tick)(void* self);
    void (*draw)(void* self);
    void (*load)(void* self);
} actor_T;

actor_T* init_actor();

actor_T* actor_constructor(
    actor_T* a,
    float x,
    float y,
    float z,
    void (*tick)(actor_T* self),
    void (*draw)(actor_T* self),
    const char* type_name
);

void actor_tick(actor_T* a);

void actor_draw(actor_T* a);

void actor_draw_default(actor_T* self, state_T* state);

void actor_free(actor_T* actor);
#endif
