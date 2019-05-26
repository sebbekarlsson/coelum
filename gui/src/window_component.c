#include "include/window_component.h"


window_component_T* window_component_constructor(window_component_T* window_component, float x, float y, void (*tick)(actor_T* self), void (*draw)(actor_T* self), const char* type_name)
{
    window_component->focused = 0;
    actor_constructor((actor_T*) window_component, x, y, 0.0f, tick, draw, type_name);

    return window_component;
}
