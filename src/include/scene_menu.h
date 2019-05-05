#ifndef PONG_SCENE_MENU_H
#define PONG_SCENE_MENU_H
#include "scene.h"
#include "dynamic_list.h"


typedef struct SCENE_MENU_STRUCT {
    scene base;
    int button_index;
    dynamic_list* buttons;
    dynamic_list* event_listeners;
} scene_menu;

scene_menu* init_scene_menu();

void scene_menu_tick(scene* self);

void scene_menu_draw(scene* self);
#endif
