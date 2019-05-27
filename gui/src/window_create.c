#include "include/window_create.h"
#include "include/text_field.h"
#include "include/label.h"


window_create_T* init_window_create(float x, float y, void (*on_close)(window_T* self, scene_T* scene))
{
    window_create_T* window_create = calloc(1, sizeof(struct WINDOW_CREATE_STRUCT));
    window_constructor((window_T*) window_create, x, y, 420, 430, "create", window_create_tick, window_create_draw, "window_create", on_close);

    window_T* window = (window_T*) window_create;
    state_T* state = window->state;

    float component_y = 96;

    window_attach_actor(
        window,
        (actor_T*) init_label(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y - 16,
            "width",
            window
        )      
    );
    window_attach_actor(
        window,
        (actor_T*) init_text_field(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y,
            200,
            32,
            window
        )
    );

    component_y += 86;
    
    window_attach_actor(
        window,
        (actor_T*) init_label(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y - 16,
            "height",
            window
        )      
    );
    window_attach_actor(
        window,
        (actor_T*) init_text_field(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y,
            200,
            32,
            window
        )
    );

    component_y += 86;

    window_attach_actor(
        window,
        (actor_T*) init_label(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y - 16,
            "texture",
            window
        )      
    );
    window_attach_actor(
        window,
        (actor_T*) init_text_field(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y,
            200,
            32,
            window
        )
    );

    component_y += 86;

    window_attach_actor(
        window,
        (actor_T*) init_label(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y - 16,
            "tick",
            window
        )      
    );
    window_attach_actor(
        window,
        (actor_T*) init_text_field(
            x - 200 / 2,
            y - ((window->height / 2)) + component_y,
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
