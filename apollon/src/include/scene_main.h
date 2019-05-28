#ifndef APOLLON_SCENE_MAIN_H
#define APOLLON_SCENE_MAIN_H
#include <coelum/scene.h>
#include <coelum/constants.h>
#include <coelum/dynamic_list.h>
#include "window_manager.h"
#include "grid.h"


typedef struct SCENE_MAIN_STRUCT {
    scene_T base;
    window_manager_T* window_manager;
    grid_T* grid;
    int cursor_x;
    int cursor_y;
} scene_main_T;

scene_main_T* init_scene_main();

void scene_main_tick(state_T* self);

void scene_main_draw(state_T* self);
#endif
