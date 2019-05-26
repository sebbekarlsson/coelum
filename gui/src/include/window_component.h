#ifndef COELUMG_WINDOW_COMPONENT_H
#define COELUMG_WINDOW_COMPONENT_H
#include <coelum/actor.h>


typedef struct WINDOW_COMPONENT_STRUCT
{
    actor_T base;
    unsigned int focused;
} window_component_T;

window_component_T* window_component_constructor(window_component_T* window_component, float x, float y, void (*tick)(actor_T* self), void (*draw)(actor_T* self), const char* type_name);
#endif
