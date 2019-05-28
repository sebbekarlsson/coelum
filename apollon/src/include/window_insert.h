#ifndef APOLLON_WINDOW_insert_H
#define APOLLON_WINDOW_insert_H
#include "window.h"


typedef struct WINDOW_insert_STRUCT
{
    window_T base;
} window_insert_T;

window_insert_T* init_window_insert(float x, float y, void (*on_close)(window_T* self, scene_T* scene));

void window_insert_tick(actor_T* self);

void window_insert_draw(actor_T* self);
#endif
