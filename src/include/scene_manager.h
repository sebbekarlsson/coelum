#ifndef PONG_SCENE_MANAGER_H
#define PONG_SCENE_MANAGER_H
#include "dynamic_list.h"
#include "scene.h"

typedef struct SCENE_MANAGER_STRUCT {
    int scene_index;
    dynamic_list* scenes;
} scene_manager;

scene_manager* init_scene_manager();

scene* get_current_scene_scene_manager(scene_manager* sm);

void append_scene_scene_manager(scene_manager* sm, scene* s);
#endif
