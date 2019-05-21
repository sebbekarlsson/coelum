#include "include/scene_main.h"
#include <coelum/constants.h>
#include <coelum/actor_text.h>
#include <coelum/input.h>
#include <coelum/scene_manager.h>


extern keyboard_state_T* KEYBOARD_STATE;

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

    s_main->grid = init_grid();

    return s_main;
}

void scene_main_tick(scene_T* self)
{
    scene_main_T* s_main = (scene_main_T*) self;

    scene_tick(self);

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

    if (KEYBOARD_STATE->keys[GLFW_KEY_V])
    {
        s_main->grid->cells[s_main->grid->cursor_x][s_main->grid->cursor_y]->selected = 1;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_C])
    {
        grid_unselect(s_main->grid);
    }
    
    grid_tick(s_main->grid); 
}

void scene_main_draw(scene_T* self)
{
    scene_main_T* s_main = (scene_main_T*) self;

    scene_draw(self);
    grid_draw(s_main->grid); 
}
