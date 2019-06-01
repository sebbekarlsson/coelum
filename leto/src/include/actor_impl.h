#ifndef LETO_ACTOR_IMPL_H
#define LETO_ACTOR_IMPL_H
#include <coelum/actor.h>


typedef struct ACTOR_IMPL_STRUCT {
    actor_T base;
    char* source_code;
} actor_impl_T;


actor_impl_T* init_actor_impl(float x, float y, float z, char* source_code, char* type_name);

void actor_impl_tick(actor_T* self);

void actor_impl_draw(actor_T* self);
#endif
