#ifndef PONG_SCENE_H
#define PONG_SCENE_H
#include "dynamic_list.h"

typedef struct SCENE_STRUCT {
    dynamic_list* actors;
} scene;

scene* init_scene();

void tick_scene(scene* s);

void draw_scene(scene* s);
#endif
