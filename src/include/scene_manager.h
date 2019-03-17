#ifndef PONG_SCENE_MANAGER_H
#define PONG_SCENE_MANAGER_H
#include "dynamic_list.h"
#include "scene.h"

typedef struct SCENE_MANAGER_STRUCT {
    int scene_index;
    dynamic_list* scenes;
} scene_manager;

scene_manager* init_scene_manager();

scene* scene_manager_get_current_scene(scene_manager* sm);

void scene_manager_register_scene(scene_manager* sm, scene* s);

void scene_manager_draw(scene_manager* sm);

void scene_manager_tick(scene_manager* sm);
#endif
