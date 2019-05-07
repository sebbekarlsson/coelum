#include "include/actor_ball.h"
#include "include/input.h"
#include "include/textures.h"
#include "include/scene_manager.h"
#include "include/scene_play.h"


extern scene_manager* SCENE_MANAGER;

float degrees = 0.0f;

void actor_ball_load(actor* self)
{
    actor_push(self, degrees, 10.0f);
}

/**
 * Creates an instancec of a ball actor.
 *
 * @param float x
 * @param float y
 * @param float z
 *
 * @return actor_ball*
 */
actor_ball* init_actor_ball(float x, float y, float z)
{
    actor_ball* ball = calloc(1, sizeof(struct ACTOR_BALL_STRUCT));
    actor* a = (actor*) ball;

    actor_constructor(a, x, y, z, actor_ball_tick, actor_ball_draw);

    a->load = actor_ball_load;
    a->type = 0;

    a->width = 16;
    a->height = 16;
    a->friction = 0.01f;

    ((actor*)ball)->texture = get_texture("res/img/redball.png", GL_RGBA)->renderable_texture;

    return ball;
}

void actor_ball_tick(actor* self)
{
    if (self->dx > 0.0f)
    {
        if (self->dx - self->friction < 0.0f)
            self->dx = 0.0f;
        else
            self->dx -= self->friction;
    }
    else if (self->dx < 0.0f)
    {
        if (self->dx + self->friction > 0.0f)
            self->dx = 0.0f;
        else
            self->dx += self->friction;
    }

    if (self->dy > 0.0f)
    {
        if (self->dy - self->friction < 0.0f)
            self->dy = 0.0f;
        else
            self->dy -= self->friction;
    }
    else if (self->dy < 0.0f)
    {
        if (self->dy + self->friction > 0.0f)
            self->dy = 0.0f;
        else
            self->dy += self->friction;
    }

    scene* current_scene = scene_manager_get_current_scene(SCENE_MANAGER);

    self->x += self->dx;
    self->y += self->dy;

    for (int i = 0; i < current_scene->actors->size; i++)
    {
        actor* a = (actor*) current_scene->actors->items[i];

        if (a->type == 1) // pad
        {
            if (self->x + self->width >= a->x - a->width && self->x - self->width <= a->x + a->width)
            {
                if (self->y + self->height >= a->y - a->height && self->y - self->height <= a->y + a->height)
                {
                    actor_push(self, 180.0f, self->dx * 2.05f);
                }
            }
        }
    }

    if (self->x < 0)
    {
        scene_play* play_scene = (scene_play*) current_scene;
        play_scene->computer_score += 1;
        self->x = 640 / 2;
        self->y = 480 / 2;
    }

    if (self->x > 640)
    {
        scene_play* play_scene = (scene_play*) current_scene;
        play_scene->player_score += 1;
        self->x = 640 / 2;
        self->y = 480 / 2;
    }
}

void actor_ball_draw(actor* self)
{
    actor_draw(self);
}
