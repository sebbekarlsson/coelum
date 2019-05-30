#ifndef LETO_SCENE_IMPL_H
#define LETO_SCENE_IMPL_H
#include <coelum/scene.h>
#include <coelum/dynamic_list.h>
#include <glad/glad.h> 

typedef struct SCENE_IMPL_STRUCT
{
    scene_T base;
    dynamic_list_T* on_load_actors;
} scene_impl_T;

typedef struct ACTOR_ABSTRACT_STRUCT
{
    char* type_name;
    float x;
    float y;
    float z;
} actor_abstract_T;

actor_abstract_T* init_actor_abstract(char* type_name, float x, float y, float z);

scene_impl_T* init_scene_impl();

void scene_impl_tick(state_T* self);

void scene_impl_draw(state_T* self);
#endif
