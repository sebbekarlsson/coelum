#ifndef APOLLON_WINDOW_H
#define APOLLON_WINDOW_H
#include <coelum/actor.h>
#include <coelum/state.h>
#include <coelum/scene.h>
#include <coelum/dynamic_list.h>


typedef struct WINDOW_STRUCT
{
    actor_T base;
    state_T* state;
    char* title;
    float width;
    float height;
    unsigned int focus_index;
    void (*on_close)(void* self, scene_T* scene);
} window_T;

window_T* init_window();

window_T* window_constructor(window_T* window, float x, float y, float width, float height, char* title, void (*tick)(actor_T* self), void (*draw)(actor_T* self), const char* type_name, void (*on_close)(window_T* self, scene_T* scene));

void window_tick(actor_T* self);

void window_draw(actor_T* self);

actor_T* window_attach_actor(window_T* window, actor_T* actor);
#endif
