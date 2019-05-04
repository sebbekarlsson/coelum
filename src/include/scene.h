#ifndef PONG_SCENE_H
#define PONG_SCENE_H
#include "dynamic_list.h"
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct SCENE_STRUCT {
    dynamic_list* actors;
    unsigned int VAO;
    mat4 projection;
    mat4 view;
} scene;

scene* init_scene();

scene* scene_constructor(scene* s);

void scene_tick(scene* s);

void scene_draw(scene* s);
#endif
