#include "include/actor_pad.h"
#include "include/input.h"
#include "include/textures.h"


extern event_manager* EVENT_MANAGER;

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
 * Called when the pad actor is loaded
 *
 * @param actor* self
 */
void actor_pad_load(actor* self)
{
    add_event_listener(EVENT_MANAGER, GLFW_KEY_UP, actor_pad_key_up_callback);
    add_event_listener(EVENT_MANAGER, GLFW_KEY_DOWN, actor_pad_key_down_callback);
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
actor_pad* init_actor_pad(float x, float y, float z)
{
    actor_pad* pad = calloc(1, sizeof(struct ACTOR_PAD_STRUCT));
    actor* a = (actor*) pad;

    a->load = actor_pad_load;

    actor_constructor(a, x, y, z, actor_pad_tick, actor_pad_draw); 

    pad->speed = 3.5f;

    ((actor*)pad)->texture = get_texture("res/img/redball.png")->renderable_texture;

    return pad;
}

void actor_pad_tick(actor* self)
{
    if (key_up)
        self->y -= ((actor_pad*)self)->speed;

    if (key_down)
        self->y += ((actor_pad*)self)->speed;
}

void actor_pad_draw(actor* self)
{
    actor_draw(self);
}
