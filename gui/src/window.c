#include "include/window.h"
#include <coelum/theatre.h>
#include <coelum/draw_utils.h>
#include <string.h>


extern theatre_T* THEATRE;

extern const float COLOR_FG[3];
extern const float COLOR_BG_DARK[3];
extern const float COLOR_BG_DARK_BRIGHT[3];

window_T* init_window()
{
    return calloc(1, sizeof(struct WINDOW_STRUCT));
}

window_T* window_constructor(window_T* window, float x, float y, float width, float height, char* title, void (*tick)(actor_T* self), void (*draw)(actor_T* self))
{
    window->title = title;
    window->width = width;
    window->height = height;
    actor_constructor((actor_T*) window, x, y, 0.0f, tick, draw);
    window->state = init_state();
    state_constructor(window->state, (void*)0, (void*)0, width, height);

    return window;
}

void window_tick(actor_T* self)
{
    window_T* window = (window_T*) self;
    state_tick(window->state);
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
