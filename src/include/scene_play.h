#ifndef PONG_SCENE_PLAY_H
#define PONG_SCENE_PLAY_H
#include "scene.h"

typedef struct SCENE_PLAY_STRUCT {
    scene base;
} scene_play;


scene_play* init_scene_play();

void scene_play_tick(scene* self);

void scene_play_draw(scene* self);
#endif
