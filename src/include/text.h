#ifndef COELUM_TEXT_H
#define COELUM_TEXT_H
#include "textures.h"
#include "state.h"


void draw_text(
    const char* text,
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    float size,
    float spacing,
    state_T* state
);
#endif
