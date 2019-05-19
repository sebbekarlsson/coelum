#ifndef COELUM_RENDER_H
#define COELUM_RENDER_H
#include "projection_view.h"

void render_2D_mesh(
    float width,
    float height,
    float r,
    float g,
    float b,
    unsigned int VBO,
    unsigned int EBO
);

void render_2D_positioned_2D_mesh(
    float x,
    float y,
    float width,
    float height,
    float r,
    float g,
    float b,
    unsigned int VAO,
    projection_view* pv
);
#endif
