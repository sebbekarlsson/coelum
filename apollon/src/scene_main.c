#include "include/scene_main.h"
#include "include/window_manager.h"
#include "include/window_create.h"
#include "include/window_insert.h"
#include "include/window_popup.h"
#include "include/text_field.h"
#include "include/select_list.h"
#include <coelum/constants.h>
#include <coelum/sound.h>
#include <coelum/actor_text.h>
#include <coelum/actor.h>
#include <coelum/textures.h>
#include <coelum/input.h>
#include <string.h>
#include <coelum/io.h>
#include <coelum/hermes/lexer.h>
#include <coelum/hermes/hermes_parser.h>
#include <coelum/hermes/hermes_runtime.h>
#include <coelum/theatre.h>


extern keyboard_state_T* KEYBOARD_STATE;
extern window_manager_T* WINDOW_MANAGER;
extern theatre_T* THEATRE;

extern const float COLOR_BG_BRIGHT[3];

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

    s->bg_r = COLOR_BG_BRIGHT[0];
    s->bg_g = COLOR_BG_BRIGHT[1];
    s->bg_b = COLOR_BG_BRIGHT[2]; 

    s_main->window_manager = init_window_manager();
    s_main->grid = init_grid();

    return s_main;
}


void remove_window_callback(void* item)
{
    window_T* window = (window_T*) item;

    /*for (int i = 0; i < window->state->actors->size; i++)
      {
      text_field_T* text_field = (text_field_T*) window->state->actors->items[i];

      if (text_field->value)
      free(text_field->value);

    //dynamic_list_remove(window->state->actors, window->state->actors->items[i], (void*)0);
    }*/

    state_free(window->state);

    actor_free((actor_T*) item);
}

void window_insert_close_callback(window_T* window, scene_T* scene)
{
    select_list_T* select_list;
    scene_main_T* s_main = (scene_main_T*) scene;
    state_T* state = (state_T*) scene;

    for (int i = 0; i < window->state->actors->size; i++)
    {
        actor_T* actor = (actor_T*) window->state->actors->items[i];

        if (strcmp(actor->type_name, "select_list") == 0)
            select_list = (select_list_T*) actor;
    }

    char* actor_type_name;
    float actor_width;
    float actor_height;
    char* actor_texture_path;
    float actor_x = s_main->grid->cursor_x * 16;
    float actor_y = s_main->grid->cursor_y * 16;

    if (select_list)
    {
        select_list_item_T* item = select_list_get_selected_item(select_list);

        actor_type_name = item->key;

        lexer_T* lexer = init_lexer(read_file("actors.txt"));
        hermes_parser_T* parser = init_hermes_parser(lexer);
        AST_T* node = hermes_parser_parse(parser, (void*) 0);
        runtime_T* runtime = init_runtime();
        runtime_visit(runtime, node);
        
        for (int i = 0; i < runtime->scope->variable_definitions->size; i++)
        {
            AST_T* ast = (AST_T*) runtime->scope->variable_definitions->items[i];

            if (ast->type != AST_VARIABLE_DEFINITION)
                continue;

            char* actor_name = ast->variable_name;

            printf("!!!%s\n", actor_name);

            if (strcmp(item->key, actor_name) == 0)
            {
                AST_T* actor_object = (AST_T*) ast->variable_value;
                hermes_scope_T* actor_object_scope = get_scope(runtime, actor_object);

                for (int j = 0; j < actor_object_scope->variable_definitions->size; j++)
                {
                    AST_T* ast_obj_var = (AST_T*) actor_object_scope->variable_definitions->items[j];

                    if (strcmp(ast_obj_var->variable_name, "texture") == 0)
                        actor_texture_path = ast_obj_var->variable_value->string_value;
                    
                    if (strcmp(ast_obj_var->variable_name, "width") == 0)
                        actor_width = ast_obj_var->variable_value->int_value;

                    if (strcmp(ast_obj_var->variable_name, "height") == 0)
                        actor_height = ast_obj_var->variable_value->int_value;
                }
            }
        }

        lexer_free(lexer); // we dont need it any more
    }

    if (actor_texture_path)
    {
        actor_T* ac = init_actor(actor_x, actor_y, 0.0f);
        actor_constructor(ac, actor_x, actor_y, 0.0f, actor_tick, actor_draw, actor_type_name);
        texture_T* texture = get_texture(actor_texture_path, GL_RGBA);
        ac->texture = texture->renderable_texture;
        ac->width = actor_width;
        ac->height = actor_height;

        dynamic_list_append(state->actors, ac);
    }

    printf("Insert window closed!\n");
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
            init_window_create(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, (void*) 0)
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
            init_window_insert(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, window_insert_close_callback)
        );


        play_sound_wav_threaded("res/sound/fret-noise.wav", THEATRE->al);

        KEYBOARD_STATE->key_locks[GLFW_KEY_I] = 1;
    } else if (!KEYBOARD_STATE->keys[GLFW_KEY_I])
    {
        KEYBOARD_STATE->key_locks[GLFW_KEY_I] = 0;
    }

    if (KEYBOARD_STATE->keys[GLFW_KEY_Q] && KEYBOARD_STATE->key_locks[GLFW_KEY_Q] == 0 && s_main->window_manager->windows->size)
    {
        window_T* window_to_close = s_main->window_manager->windows->items[s_main->window_manager->windows->size - 1];

        if (window_to_close->on_close)
            window_to_close->on_close(window_to_close, scene);

        dynamic_list_remove(
            s_main->window_manager->windows,
            window_to_close,
            remove_window_callback
        );

        KEYBOARD_STATE->key_locks[GLFW_KEY_Q] == 1;
    } else if (!KEYBOARD_STATE->keys[GLFW_KEY_Q])
    {
        KEYBOARD_STATE->key_locks[GLFW_KEY_Q] == 0;
    }

    if (
       KEYBOARD_STATE->keys[GLFW_KEY_LEFT_CONTROL] && KEYBOARD_STATE->key_locks[GLFW_KEY_LEFT_CONTROL] == 0 &&
       KEYBOARD_STATE->keys[GLFW_KEY_S] && KEYBOARD_STATE->key_locks[GLFW_KEY_S] == 0
    )
    {
        dynamic_list_append(
            s_main->window_manager->windows,
            init_window_popup(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "saved", (void*) 0)
        ); 
        
        KEYBOARD_STATE->key_locks[GLFW_KEY_LEFT_CONTROL] = 1;
        KEYBOARD_STATE->key_locks[GLFW_KEY_S] = 1;
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
