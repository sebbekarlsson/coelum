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
    mat4 model;
} actor;

actor* init_actor(float x, float y, float z);

void actor_tick(actor* a);

void draw_actor(actor* a);
#endif
