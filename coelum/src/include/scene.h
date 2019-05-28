#ifndef COELUM_SCENE_H
#define COELUM_SCENE_H
#include "state.h"
#include "dynamic_list.h"
#include "camera.h"
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct SCENE_STRUCT
{
    state_T base; 
    float bg_r;
    float bg_g;
    float bg_b;
    void (*load)(void* self);
    void (*unload)(void* self);
} scene_T;

scene_T* init_scene();

scene_T* scene_constructor(scene_T* scene, void (*tick)(state_T* self), void (*draw)(state_T* self));

void scene_tick(scene_T* scene);

void scene_draw(scene_T* scene);
#endif
