#ifndef COELUM_DRAW_UTILS_H
#define COELUM_DRAW_UTILS_H
#include "projection_view.h"

void send_projection_view_state(unsigned int shader_program, projection_view_T* projection_view);
void send_model_state(unsigned int shader_program, mat4 model);

void draw_2D_mesh(
    float width,
    float height,
    float r,
    float g,
    float b,
    unsigned int VBO,
    unsigned int EBO
);

void draw_2D_positioned_2D_mesh(
    float x,
    float y,
    float width,
    float height,
    float r,
    float g,
    float b,
    unsigned int VAO,
    projection_view_T* projection_view
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
    unsigned int VAO,
    projection_view_T* projection_view
);
#endif