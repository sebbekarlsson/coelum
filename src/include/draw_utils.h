#ifndef COELUM_DRAW_UTILS_H
#define COELUM_DRAW_UTILS_H
#include "projection_view.h"
#include "state.h"
#include "sprite.h"
#include <objload/obj.h>


void send_projection_view_state(
    unsigned int shader_program,
    projection_view_T* projection_view
);

void send_model_state(unsigned int shader_program, mat4 model);

void draw_2D_mesh(
    float width,
    float height,
    float r,
    float g,
    float b,
    float a,
    unsigned int VBO,
    unsigned int EBO
);

void draw_positioned_2D_mesh(
    float x,
    float y,
    float z,
    float width,
    float height,
    float r,
    float g,
    float b,
    float a,
    state_T* state
);

void draw_positioned_sprite(
    sprite_T* sprite,
    float x,
    float y,
    float z,
    float width,
    float height,
    state_T* state
);

void draw_line(
    float x,
    float y,
    float z,
    float endx,
    float endy,
    float endz,
    float r,
    float g,
    float b,
    state_T* state
);

void draw_3D_axis(float x, float y, float z, float width, float height, float depth, state_T* state);

void draw_text(
    const char* text,
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    float a,
    float size,
    float spacing,
    unsigned int limit,
    state_T* state
);

void draw_3D_model(
    obj_T* obj,
    unsigned int texture,
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    state_T* state
);
#endif
