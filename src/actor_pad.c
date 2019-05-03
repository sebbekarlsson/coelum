#include "include/actor_pad.h"
#include "include/input.h"
#include "include/textures.h"
#include "include/text.h"


extern event_manager* EVENT_MANAGER;

int key_up = 0;
int key_down = 0;

void actor_pad_key_up_callback(int state) {
    key_up = state;
}

void actor_pad_key_down_callback(int state) {
    key_down = state;
}

actor_pad* init_actor_pad(float x, float y, float z) {
    actor_pad* pad = calloc(1, sizeof(struct ACTOR_PAD_STRUCT));

    pad->speed = 3.5f;

    actor_constructor((actor*) pad, x, y, z, actor_pad_tick, actor_pad_draw);

    add_event_listener(EVENT_MANAGER, GLFW_KEY_UP, actor_pad_key_up_callback);
    add_event_listener(EVENT_MANAGER, GLFW_KEY_DOWN, actor_pad_key_down_callback);

    ((actor*)pad)->texture = get_texture("res/img/redball.png")->renderable_texture;
    //((actor*)pad)->texture = get_char_texture_from_texture('e', 7, 7, 8, 12, get_texture("res/font/null_terminator.png"));

    return pad;
};


void actor_pad_tick(actor* self) {
    if (key_up)
        self->y -= ((actor_pad*)self)->speed;

    if (key_down)
        self->y += ((actor_pad*)self)->speed;
}

void actor_pad_draw(actor* self) {
    //printf("actor_pad_draw\n");
    actor_draw(self);
    render_text("hello");
}
