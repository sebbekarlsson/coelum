#include "include/window_create.h"
#include "include/text_field.h"


window_create_T* init_window_create(float x, float y)
{
    window_create_T* window_create = calloc(1, sizeof(struct WINDOW_CREATE_STRUCT));
    window_constructor((window_T*) window_create, x, y, 420, 430, "create", window_create_tick, window_create_draw, "window_create");

    window_T* window = (window_T*) window_create;
    state_T* state = window->state;

    dynamic_list_append(
        state->actors,
        init_text_field(
            x - 200 / 2,
            y,
            200,
            32,
            window
        )
    );

    return window_create;
}

void window_create_tick(actor_T* self)
{
    window_tick(self);
}

void window_create_draw(actor_T* self)
{
    window_draw(self);
}
