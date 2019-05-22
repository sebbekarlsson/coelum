#ifndef COELUMG_WINDOW_MANAGER_H
#define COELUMG_WINDOW_MANAGER_H
#include <coelum/dynamic_list.h>
#include <coelum/actor.h>


typedef struct WINDOW_STRUCT
{
    actor_T base;
    char* title;
    float width;
    float height;
} window_T;

typedef struct WINDOW_MANAGER_STRUCT
{
    dynamic_list_T* windows;
} window_manager_T;


window_T* init_window(float x, float y, float width, float height, char* title);

void window_tick(actor_T* self);

void window_draw(actor_T* self);

window_manager_T* init_window_manager();

void window_manager_tick(window_manager_T* window_manager);

void window_manager_draw(window_manager_T* window_manager);
#endif
