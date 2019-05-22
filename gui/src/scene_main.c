#include "include/scene_main.h"
#include "include/window_manager.h"
#include <coelum/constants.h>
#include <coelum/actor_text.h>
#include <coelum/input.h>


extern keyboard_state_T* KEYBOARD_STATE;
extern window_manager_T* WINDOW_MANAGER;

int KEY_C_LATCH = 0;
int KEY_I_LATCH = 0;

/**
 * Creates a new scene_main
 *
 * @return scene_main_T*
 */
scene_main_T* init_scene_main()
{
    scene_main_T* s_main = calloc(1, sizeof(struct SCENE_MAIN_STRUCT));
    scene_T* s = (scene_T*) s_main;

    scene_constructor(s, scene_main_tick, scene_main_draw);

    s->bg_r = 251.0f;
    s->bg_g = 241.0f;
    s->bg_b = 199.0f; 

    s_main->window_manager = init_window_manager();
    s_main->grid = init_grid();


    return s_main;
}

void scene_main_tick(scene_T* self)
{
    scene_main_T* s_main = (scene_main_T*) self;

    scene_tick(self);

    window_manager_tick(s_main->window_manager);

    if (KEYBOARD_STATE->keys[GLFW_KEY_UP])
    {
        s_main->grid->cursor_y -= 1;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_DOWN])
    {
        s_main->grid->cursor_y += 1;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_LEFT])
    {
        s_main->grid->cursor_x -= 1;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_RIGHT])
    {
        s_main->grid->cursor_x += 1;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_S])
    {
        s_main->grid->cells[s_main->grid->cursor_x][s_main->grid->cursor_y]->selected = 1;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_D])
    {
        grid_unselect(s_main->grid);
    }
    
    if (KEYBOARD_STATE->keys[GLFW_KEY_C] && KEY_C_LATCH == 0)
    {
        dynamic_list_append(s_main->window_manager->windows, init_window(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 420, 340, "create"));
        KEY_C_LATCH = 1;
    } else if (!KEYBOARD_STATE->keys[GLFW_KEY_C])
    {
        KEY_C_LATCH = 0;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_I] && KEY_I_LATCH == 0)
    {
        dynamic_list_append(s_main->window_manager->windows, init_window(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 420, 340, "insert"));
        KEY_I_LATCH = 1;
    } else if (!KEYBOARD_STATE->keys[GLFW_KEY_I])
    {
        KEY_I_LATCH = 0;
    }
    
    grid_tick(s_main->grid); 
}

void scene_main_draw(scene_T* self)
{
    scene_main_T* s_main = (scene_main_T*) self;

    scene_draw(self);
    grid_draw(s_main->grid); 
    
    window_manager_draw(s_main->window_manager);
}
