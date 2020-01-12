#ifndef COMPONENT_H
#define COMPONENT_H
#include "actor.h"


struct COMPONENT_STRUCT;

typedef void (*component_tick)(struct COMPONENT_STRUCT* component, actor_T* actor);
typedef void (*component_draw)(struct COMPONENT_STRUCT* component, actor_T* actor);

typedef struct COMPONENT_STRUCT
{
    component_tick tick;
    component_draw draw;
} component_T;

component_T* init_component(component_tick tick, component_draw draw);

void component_free(component_T* component);
#endif
