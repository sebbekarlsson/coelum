#include "include/component.h"


component_T* init_component(component_tick tick, component_draw draw)
{
    component_T* component = calloc(1, sizeof(struct COMPONENT_STRUCT));
    component->tick = tick;
    component->draw = draw;

    return component;
}

void component_free(component_T* component)
{
    free(component);
}
