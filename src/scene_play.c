#include "include/scene_play.h"
#include "include/actor_pad.h"
#include "include/actor_ball.h"
#include "include/render.h"
#include "include/utils.h"
#include <string.h>


void scene_play_load(scene* self)
{
    scene_play* s_play = (scene_play*) self;

    s_play->player_score = 0;
    s_play->computer_score = 0;

    for (int i = 0; i < self->actors->size; i++)
    {
        actor* a = (actor*) self->actors->items[i];

        if (a->type == 0) // ball
        {
            a->x = 640.0f / 2;
            a->y = (480.0f / 2) - 16;
        }
        else if (a->type == 1) // pad
        {
            actor_pad* pad = (actor_pad*) a;

            if (pad->player)
            {
                a->x = 16.0f;
                a->y = (480.0f / 2) - 32;
            }
            else
            {
                a->x = 640.0f - 32.0f;
                a->y = (480.0f / 2) - 32;
            }
        }
    }

    init_random();
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
    s_play->text_player_score = init_actor_text((640.0f / 2) - 120.0f, 64.0f, 0.0f, "0", 255, 255, 255);
    s_play->text_computer_score = init_actor_text((640.0f / 2) + 120.0f, 64.0f, 0.0f, "0", 255, 255, 255);
    s_play->text_player_score_buffer = calloc(16, sizeof(char));
    s_play->text_computer_score_buffer = calloc(16, sizeof(char));

    dynamic_list_append(s->actors, init_actor_pad(16.0f, (480.0f / 2) - 32, 0.0f, 1));
    dynamic_list_append(s->actors, init_actor_pad(640.0f - 32.0f, (480.0f / 2) - 32, 0.0f, 0));
    dynamic_list_append(s->actors, init_actor_ball(640.0f / 2, (480.0f / 2) - 16, 0.0f));

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

    if (s_play->player_score >= 10 || s_play->computer_score >= 10)
    {
        scene_play_load(self);
    }
}

void scene_play_draw(scene* self)
{

    render_2D_positioned_2D_mesh(640.0f / 2, 0.0f, 16.0f, 480.0f, 255.0f, 255.0f, 255.0f, self->VAO);
    
    scene_draw(self);
}
