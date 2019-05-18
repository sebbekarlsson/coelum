#include "include/actor_pad.h"
#include "include/input.h"
#include "include/textures.h"
#include "include/scene_manager.h"
#include "include/utils.h"
#include <time.h>


extern scene_manager* SCENE_MANAGER;
extern keyboard_state* KEYBOARD_STATE;

extern unsigned int SHADER_COLORED;

int key_up = 0;
int key_down = 0;

void actor_pad_key_up_callback(int state)
{
    key_up = state;
}

void actor_pad_key_down_callback(int state)
{
    key_down = state;
}

/**
 * Creates an instancec of a pad actor.
 *
 * @param float x
 * @param float y
 * @param float z
 *
 * @return actor_pad*
 */
actor_pad* init_actor_pad(float x, float y, float z, int player)
{
    actor_pad* pad = calloc(1, sizeof(struct ACTOR_PAD_STRUCT));
    actor* a = (actor*) pad;

    actor_constructor(a, x, y, z, actor_pad_tick, actor_pad_draw);
    
    a->type = 1;

    a->shader_program = SHADER_COLORED;
    a->width = 16;
    a->height = 48;

    pad->player = player;
    pad->speed = 4.5f;
    pad->target_x = 640 / 2;
    pad->target_y = y;
    pad->target_y_error = 0.0f;
    pad->use_error = 0;

    return pad;
}

void actor_pad_tick(actor* self)
{
    actor_pad_key_up_callback(KEYBOARD_STATE->keys[GLFW_KEY_UP]);
    actor_pad_key_down_callback(KEYBOARD_STATE->keys[GLFW_KEY_DOWN]);

    actor_pad* pad = (actor_pad*) self;

    if (pad->player)
    {
        if (key_up && self->y > 0)
            self->y -= ((actor_pad*)self)->speed;

        if (key_down && self->y + self->height < 480.0f)
            self->y += ((actor_pad*)self)->speed;
    }
    else
    {
        scene* current_scene = scene_manager_get_current_scene(SCENE_MANAGER);

        actor* player = (void*) 0;
        actor* ball = (void*) 0;

        for (int i = 0; i < current_scene->actors->size; i++)
        {
            actor* a = (actor*) current_scene->actors->items[i];

            if (a->type == 0) // ball
            {
                ball = a;
            }
            else
            if (a->type == 1 && a != self)
            {
                player = a;
            }
        }

        pad->target_y = ball->y;
        
        int chance = 32;

        if (ball->x < 640 / 2)
            chance -= 8;

        if (pad->use_error)
        {
            pad->target_y += pad->target_y_error;
            chance = 8;
        }

        if (random_int(0, chance) == 1) // toggle error on and off
        {
            if (pad->use_error)
                pad->use_error = 0;
            else
                pad->use_error = 1;
        }

        if (random_int(0, 8) == 0)
        {
            pad->target_y_error = random_int(-480, 480);
        }

        if (self->y < pad->target_y)
        {
            self->y += pad->speed;
        }
        else
        if (self->y > pad->target_y)
        {
            self->y -= pad->speed;
        }
    }
}

void actor_pad_draw(actor* self)
{
    actor_draw(self);
}
