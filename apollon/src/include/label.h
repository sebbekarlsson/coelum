#ifndef APOLLON_LABEL_H
#define APOLLON_LABEL_H
#include "window.h"
#include "window_component.h"
#include <glad/glad.h> 


typedef struct LABEL_STRUCT
{
    window_component_T base;
    char* value;
    window_T* window;
} label_T;

label_T* init_label(float x, float y, char* value, window_T* window);

void label_tick(actor_T* self);

void label_draw(actor_T* self);
#endif
