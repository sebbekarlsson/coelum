#ifndef PONG_SCENE_MENU_H
#define PONG_SCENE_MENU_H
#include "scene.h"


typedef struct SCENE_MENU_STRUCT {
    scene base;
} scene_menu;

scene_menu* init_scene_menu();

void scene_menu_tick(scene* self);

void scene_menu_draw(scene* self);
#endif
