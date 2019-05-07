#include "include/scene_play.h"
#include "include/actor_pad.h"
#include "include/actor_ball.h"
#include <string.h>


void scene_play_load(scene* self)
{
    scene_play* s_play = (scene_play*) self;

    s_play->player_score = 0;
    s_play->computer_score = 0;
}

/**
 * Creates a new scene_play
 *
 * @return scene_play*
 */
scene_play* init_scene_play()
{
    scene_play* s_play = calloc(1, sizeof(struct SCENE_PLAY_STRUCT));
    scene* s = (scene*) s_play;
    scene_constructor(s, scene_play_tick, scene_play_draw);

    s_play->player_score = 0;
    s_play->computer_score = 0;
    s_play->text_player_score = init_actor_text(48.0f, 480.0f - 48.0f, 0.0f, "0", 255, 255, 255);
    s_play->text_computer_score = init_actor_text(640.0f - 8 * 24, 480.0f - 48.0f, 0.0f, "0", 255, 255, 255);
    s_play->text_player_score_buffer = calloc(16, sizeof(char));
    s_play->text_computer_score_buffer = calloc(16, sizeof(char));

    dynamic_list_append(s->actors, init_actor_pad(48.0f, 480.0f / 2, 0.0f, 1));
    dynamic_list_append(s->actors, init_actor_pad(640.0f - 48.0f, 480.0f / 2, 0.0f, 0));
    dynamic_list_append(s->actors, init_actor_ball(640.0f / 2, 480.0f / 2, 0.0f));

    dynamic_list_append(s->actors, init_actor_text(48.0f, 480.0f - 72.0f, 0.0f, "you", 255, 255, 255));
    dynamic_list_append(s->actors, init_actor_text(640.0f - 8 * 24, 480.0f - 72.0f, 0.0f, "computer", 255, 255, 255));
    dynamic_list_append(s->actors, s_play->text_player_score);
    dynamic_list_append(s->actors, s_play->text_computer_score);

    return s_play;
}

void scene_play_tick(scene* self)
{
    scene_tick(self);
    scene_play* s_play = (scene_play*) self; 

    sprintf(s_play->text_player_score_buffer, "%d", s_play->player_score);
    s_play->text_player_score->text = s_play->text_player_score_buffer;

    sprintf(s_play->text_computer_score_buffer, "%d", s_play->computer_score);
    s_play->text_computer_score->text = s_play->text_computer_score_buffer;
}

void scene_play_draw(scene* self)
{
    scene_draw(self);
}
