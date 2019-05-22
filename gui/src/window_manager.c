#include "include/window_manager.h"
#include <coelum/draw_utils.h>
#include <coelum/text.h>
#include <coelum/scene_manager.h>
#include <string.h>


extern scene_manager_T* SCENE_MANAGER;

window_T* init_window(float x, float y, float width, float height, char* title)
{
    window_T* w = calloc(1, sizeof(struct WINDOW_STRUCT));
    w->title = title;
    w->width = width;
    w->height = height;
    actor_constructor((actor_T*) w, x, y, 0.0f,window_tick, window_draw);

    return w;
}

void window_tick(actor_T* self)
{
}

void window_draw(actor_T* self)
{
    window_T* window = (window_T*) self;
    scene_T* scene = scene_manager_get_current_scene(SCENE_MANAGER);

    draw_2D_positioned_2D_mesh(
        self->x - (window->width / 2),
        self->y - (window->height / 2),
        window->width,
        window->height,
        168,
        153,
        132,
        scene->VAO,
        scene->camera->projection_view
    );

    draw_2D_positioned_2D_mesh(
        self->x - (window->width / 2),
        self->y - (window->height / 2),
        window->width,
        64,
        189,
        174,
        147,
        scene->VAO,
        scene->camera->projection_view
    );

    float text_size = 6;
    float text_spacing = text_size + 6; 

    draw_text(
        window->title,
        self->x - (((text_size + text_spacing) * strlen(window->title)) / 2),
        self->y - (window->height / 2) + (64 / 2),
        0.0f,
        60.0f,
        56.0f,
        54.0f,
        text_size,
        text_spacing
    );
}

window_manager_T* init_window_manager()
{
    window_manager_T* wm = calloc(1, sizeof(struct WINDOW_MANAGER_STRUCT));
    wm->windows = init_dynamic_list(sizeof(struct WINDOW_STRUCT));

    return wm;
}

void window_manager_tick(window_manager_T* window_manager)
{
    for (int i = 0; i < window_manager->windows->size; i++)
    {
        actor_T* a = window_manager->windows->items[i];
        a->tick(a);
    }
}

void window_manager_draw(window_manager_T* window_manager)
{
    for (int i = 0; i < window_manager->windows->size; i++)
    {
        actor_T* a = window_manager->windows->items[i];
        a->draw(a);
    }
}
