#include "include/actor_ball.h"
#include "include/input.h"
#include "include/textures.h"

float degrees = 0.0f;
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

    a->width = 16;
    a->height = 16;
    a->friction = 1.5f;

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

    actor_push(self, degrees, 1.7f);
    //degrees += 5;

    self->x += self->dx;
    self->y += self->dy;
}

void actor_ball_draw(actor* self)
{
    actor_draw(self);
}
