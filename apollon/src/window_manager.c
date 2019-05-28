#include "include/window_manager.h"
#include "include/window.h"
#include <coelum/actor.h>
#include <coelum/draw_utils.h>
#include <string.h>


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
