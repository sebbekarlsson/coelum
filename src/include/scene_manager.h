#ifndef COELUM_SCENE_MANAGER_H
#define COELUM_SCENE_MANAGER_H
#include "dynamic_list.h"
#include "scene.h"


typedef struct SCENE_MANAGER_STRUCT {
    int scene_index;
    dynamic_list_T* scenes;
} scene_manager_T;

scene_manager_T* init_scene_manager();

scene_T* scene_manager_get_current_scene(scene_manager_T* scene_manager);

void scene_manager_register_scene(scene_manager_T* scene_manager, scene_T* scene);

void scene_manager_draw(scene_manager_T* scene_manager);

void scene_manager_tick(scene_manager_T* scene_manager);

void scene_manager_next(scene_manager_T* scene_manager);
#endif
