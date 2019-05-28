#ifndef APOLLON_WINDOW_CREATE_H
#define APOLLON_WINDOW_CREATE_H
#include "window.h"


typedef struct WINDOW_CREATE_STRUCT
{
    window_T base;
} window_create_T;

window_create_T* init_window_create(float x, float y, void (*on_close)(window_T* self, scene_T* scene));

void window_create_tick(actor_T* self);

void window_create_draw(actor_T* self);
#endif
