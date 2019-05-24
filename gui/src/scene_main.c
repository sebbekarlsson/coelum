#include "include/scene_main.h"
#include "include/window_manager.h"
#include "include/window_create.h"
#include "include/window_insert.h"
#include "include/text_field.h"
#include <coelum/constants.h>
#include <coelum/actor_text.h>
#include <coelum/actor.h>
#include <coelum/input.h>


extern keyboard_state_T* KEYBOARD_STATE;
extern window_manager_T* WINDOW_MANAGER;

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


void remove_window_callback(void* item)
{
    window_T* window = (window_T*) item;
    
    for (int i = 0; i < window->state->actors->size; i++)
    {
        text_field_T* text_field = (text_field_T*) window->state->actors->items[i];

        if (text_field->value)
            free(text_field->value);

        //dynamic_list_remove(window->state->actors, window->state->actors->items[i], (void*)0);
    }

    state_free(window->state);

    actor_free((actor_T*) item);
}

void handle_inputs(state_T* self)
{
    scene_T* scene = (scene_T*) self;
    scene_main_T* s_main = (scene_main_T*) scene;

    if (KEYBOARD_STATE->keys[GLFW_KEY_UP])
        s_main->grid->cursor_y -= 1;

    if (KEYBOARD_STATE->keys[GLFW_KEY_DOWN])
        s_main->grid->cursor_y += 1;

    if (KEYBOARD_STATE->keys[GLFW_KEY_LEFT])
        s_main->grid->cursor_x -= 1;

    if (KEYBOARD_STATE->keys[GLFW_KEY_RIGHT])
        s_main->grid->cursor_x += 1;

    if (KEYBOARD_STATE->keys[GLFW_KEY_S])
        s_main->grid->cells[s_main->grid->cursor_x][s_main->grid->cursor_y]->selected = 1;

    if (KEYBOARD_STATE->keys[GLFW_KEY_D])
        grid_unselect(s_main->grid);
    
    if (KEYBOARD_STATE->keys[GLFW_KEY_C] && KEYBOARD_STATE->key_locks[GLFW_KEY_C] == 0)
    {
        dynamic_list_append(
            s_main->window_manager->windows,
            init_window_create(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)
        );

        KEYBOARD_STATE->key_locks[GLFW_KEY_C] = 1;
    } else if (!KEYBOARD_STATE->keys[GLFW_KEY_C])
    {
        KEYBOARD_STATE->key_locks[GLFW_KEY_C] = 0;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_I] && KEYBOARD_STATE->key_locks[GLFW_KEY_I] == 0)
    {
        dynamic_list_append(
            s_main->window_manager->windows,
            init_window_insert(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)
        );

        KEYBOARD_STATE->key_locks[GLFW_KEY_I] = 1;
    } else if (!KEYBOARD_STATE->keys[GLFW_KEY_I])
    {
        KEYBOARD_STATE->key_locks[GLFW_KEY_I] = 0;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_Q] && KEYBOARD_STATE->key_locks[GLFW_KEY_Q] == 0 && s_main->window_manager->windows->size)
    {
        dynamic_list_remove(
            s_main->window_manager->windows,
            s_main->window_manager->windows->items[s_main->window_manager->windows->size - 1],
            remove_window_callback
        );

        KEYBOARD_STATE->key_locks[GLFW_KEY_Q] == 1;
    } else if (!KEYBOARD_STATE->keys[GLFW_KEY_Q])
    {
        KEYBOARD_STATE->key_locks[GLFW_KEY_Q] == 0;
    }
}


void scene_main_tick(state_T* self)
{
    scene_T* scene = (scene_T*) self;
    scene_main_T* s_main = (scene_main_T*) scene;

    scene_tick(scene);

    window_manager_tick(s_main->window_manager);

    handle_inputs(self); 
    
    grid_tick(s_main->grid); 
}

void scene_main_draw(state_T* self)
{
    scene_T* scene = (scene_T*) self;
    scene_main_T* s_main = (scene_main_T*) self;

    scene_draw(scene);
    grid_draw(s_main->grid); 
    
    window_manager_draw(s_main->window_manager);
}
