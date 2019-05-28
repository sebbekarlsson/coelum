#ifndef APOLLON_TEXT_FIELD_H
#define APOLLON_TEXT_FIELD_H
#include "window.h"
#include "window_component.h"
#include <glad/glad.h> 


typedef struct TEXT_FIELD_STRUCT
{
    window_component_T base;
    char* value;
    float width;
    float height;
    window_T* window;
} text_field_T;

text_field_T* init_text_field(float x, float y, float width, float height, window_T* window);

void text_field_tick(actor_T* self);

void text_field_draw(actor_T* self);
#endif
