#include "include/window.h"
#include "include/window_component.h"
#include <coelum/theatre.h>
#include <coelum/draw_utils.h>
#include <coelum/input.h>
#include <string.h>


extern theatre_T* THEATRE;
extern keyboard_state_T* KEYBOARD_STATE;

extern const float COLOR_FG[3];
extern const float COLOR_BG_DARK[3];
extern const float COLOR_BG_DARK_BRIGHT[3];

window_T* init_window()
{
    return calloc(1, sizeof(struct WINDOW_STRUCT));
}

window_T* window_constructor(window_T* window, float x, float y, float width, float height, char* title, void (*tick)(actor_T* self), void (*draw)(actor_T* self), const char* type_name, void (*on_close)(window_T* self, scene_T* scene))
{
    window->title = title;
    window->width = width;
    window->height = height;
    actor_constructor((actor_T*) window, x, y, 0.0f, tick, draw, type_name);
    window->state = init_state();
    state_constructor(window->state, (void*)0, (void*)0, width, height);
    window->focus_index = 0;
    window->on_close = on_close;

    return window;
}

void window_tick(actor_T* self)
{
    window_T* window = (window_T*) self;
    state_tick(window->state);

    for (int i = 0; i < window->state->actors->size; i++)
    {
        actor_T* actor = (actor_T*) window->state->actors->items[i];
        window_component_T* window_component;

        /* if more "focusable" actors are implemented, they also need to be
         * string-compared here.
         */
        if (strcmp(actor->type_name, "text_field") == 0 || strcmp(actor->type_name, "select_list") == 0)
            window_component = (window_component_T*) actor;

        if (window->focus_index == i)
        {
            if (window_component)
                window_component->focused = 1;
        }
        else
        {
            if (window_component)
                window_component->focused = 0;
        }
    }

    // tab through "focusable" actors.
    if (KEYBOARD_STATE->keys[GLFW_KEY_TAB] && KEYBOARD_STATE->key_locks[GLFW_KEY_TAB] == 0)
    {
        if (window->focus_index < window->state->actors->size - 1)
        {
            window->focus_index += 1;
        }
        else
        {
            window->focus_index = 0;
        }

        KEYBOARD_STATE->key_locks[GLFW_KEY_TAB] = 1;
    }
}

void window_draw(actor_T* self)
{
    window_T* window = (window_T*) self;
    scene_T* scene = scene_manager_get_current_scene(THEATRE->scene_manager);
    state_T* state = (state_T*) scene;

    draw_2D_positioned_2D_mesh(
        self->x - (window->width / 2),
        self->y - (window->height / 2),
        window->width,
        window->height,
        COLOR_BG_DARK[0],
        COLOR_BG_DARK[1],
        COLOR_BG_DARK[2],
        state
    );

    draw_2D_positioned_2D_mesh(
        self->x - (window->width / 2),
        self->y - (window->height / 2),
        window->width,
        64,
        COLOR_BG_DARK_BRIGHT[0],
        COLOR_BG_DARK_BRIGHT[1],
        COLOR_BG_DARK_BRIGHT[2],
        state
    );

    float text_size = 6;
    float text_spacing = text_size + 6; 

    draw_text(
        window->title,
        self->x - (((text_size + text_spacing) * strlen(window->title)) / 2),
        self->y - (window->height / 2) + (64 / 2),
        0.0f,
        COLOR_FG[0],
        COLOR_FG[1],
        COLOR_FG[2],
        text_size,
        text_spacing,
        state
    );
    
    state_draw(window->state);
}

actor_T* window_attach_actor(window_T* window, actor_T* actor)
{
    return (actor_T*) dynamic_list_append(window->state->actors, actor);
}
