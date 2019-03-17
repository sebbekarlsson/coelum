#ifndef PONG_SCENE_H
#define PONG_SCENE_H
#include "dynamic_list.h"

typedef struct SCENE_STRUCT {
    dynamic_list* actors;
    unsigned int VAO;
} scene;

scene* init_scene();

void scene_tick(scene* s);

void scene_draw(scene* s);
#endif
