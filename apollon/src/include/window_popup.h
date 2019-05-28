#ifndef APOLLON_WINDOW_POPUP_H
#define APOLLON_WINDOW_POPUP_H
#include "window.h"


typedef struct WINDOW_POPUP_STRUCT
{
    window_T base;
    char* message;
} window_popup_T;

window_popup_T* init_window_popup(float x, float y, char* message, void (*on_close)(window_T* self, scene_T* scene));

void window_popup_tick(actor_T* self);

void window_popup_draw(actor_T* self);
#endif
