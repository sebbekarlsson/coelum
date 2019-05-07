#ifndef PONG_SCENE_PLAY_H
#define PONG_SCENE_PLAY_H
#include "scene.h"
#include "actor_text.h"


typedef struct SCENE_PLAY_STRUCT {
    scene base;
    int player_score;
    int computer_score;
    actor_text* text_player_score;
    actor_text* text_computer_score;
    char* text_player_score_buffer;
    char* text_computer_score_buffer;
} scene_play;

scene_play* init_scene_play();

void scene_play_tick(scene* self);

void scene_play_draw(scene* self);
#endif
