#include "include/actor_pad.h"
#include "include/input.h"


extern event_manager* EVENT_MANAGER;

int pressed = 0;

void key_callback(int state) {
    if (state == GLFW_PRESS)
        pressed = 1;
}


actor_pad* init_actor_pad(float x, float y, float z) {
    actor_pad* pad = calloc(1, sizeof(struct ACTOR_PAD_STRUCT));

    actor_constructor((actor*) pad, x, y, z, actor_pad_tick, actor_pad_draw);

    add_event_listener(EVENT_MANAGER, GLFW_KEY_ENTER, key_callback);

    return pad;
};


void actor_pad_tick(actor* self) {
    if (pressed)
        self->x += 1.0f;

    pressed = 0;
    //printf("actor_pad_tick\n");
    //self->x += 0.5;
}

void actor_pad_draw(actor* self) {
    //printf("actor_pad_draw\n");
    actor_draw(self);
}
