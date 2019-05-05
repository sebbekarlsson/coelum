#include "include/scene_menu.h"
#include "include/actor_pad.h"
#include "include/actor_text.h"
#include "include/input.h"
#include "include/scene_manager.h"


extern scene_manager* SCENE_MANAGER;
extern event_manager* EVENT_MANAGER;
extern GLFWwindow* window;

/**
 * Called when the enter key is pressed or released.
 *
 * @param int state
 */
void scene_menu_key_enter_callback(int state)
{
    scene_menu* s_menu = (scene_menu*) scene_manager_get_current_scene(SCENE_MANAGER);

    if (state)
    {
        switch (s_menu->button_index)
        {
            case 0:
                // "play" button
                
                scene_manager_next(SCENE_MANAGER);
            break;
            case 1:
                // "quit" button
                
                glfwSetWindowShouldClose(window, 1);
            break;
        }
    }
}

/**
 * Called when the key up is pressed or released.
 *
 * @param int state
 */
void scene_menu_key_up_callback(int state)
{
    scene_menu* s_menu = (scene_menu*) scene_manager_get_current_scene(SCENE_MANAGER);

    if (s_menu->button_index > 0)
        s_menu->button_index -= 1; 
}

/**
 * Called when the key down is pressed or released.
 *
 * @param int state
 */
void scene_menu_key_down_callback(int state)
{
    scene_menu* s_menu = (scene_menu*) scene_manager_get_current_scene(SCENE_MANAGER);

    if (s_menu->button_index < s_menu->buttons->size - 1)
        s_menu->button_index += 1; 
}

/**
 * Called when the menu scene is loaded
 *
 * @param scene* self
 */
void scene_menu_load(scene* self)
{
    scene_menu* s_menu = (scene_menu*) self;

    for (int i = 0; i < s_menu->event_listeners->size; i++)
    {
        event_listener* el = (event_listener*) s_menu->event_listeners->items[i];
        el->enabled = 1;
    }
}

/**
 * Called when the menu scene is unloaded
 *
 * @param scene* self
 */
void scene_menu_unload(scene* self)
{
    scene_menu* s_menu = (scene_menu*) self;

    for (int i = 0; i < s_menu->event_listeners->size; i++)
    {
        event_listener* el = (event_listener*) s_menu->event_listeners->items[i];
        el->enabled = 0;
    }
}

/**
 * Creates a new scene_menu
 *
 * @return scene_menu*
 */
scene_menu* init_scene_menu()
{
    scene_menu* s_menu = calloc(1, sizeof(struct SCENE_MENU_STRUCT));
    scene* s = (scene*) s_menu;

    s->load = scene_menu_load;
    s->unload = scene_menu_unload;

    scene_constructor(s, scene_menu_tick, scene_menu_draw);

    s_menu->button_index = 0;
    s_menu->buttons = init_dynamic_list(sizeof(struct ACTOR_TEXT_STRUCT));

    s_menu->event_listeners = init_dynamic_list(sizeof(struct EVENT_LISTENER_STRUCT));

    dynamic_list_append(
        s_menu->event_listeners,
        add_event_listener(EVENT_MANAGER, GLFW_KEY_ENTER, scene_menu_key_enter_callback)
    );

    dynamic_list_append(
        s_menu->event_listeners,
        add_event_listener(EVENT_MANAGER, GLFW_KEY_UP, scene_menu_key_up_callback)
    );

    dynamic_list_append(
        s_menu->event_listeners,
        add_event_listener(EVENT_MANAGER, GLFW_KEY_DOWN, scene_menu_key_down_callback)
    );

    actor_text* play_button = init_actor_text((640 / 2) - ((3 * 24) / 2), (480 / 2) - 16, 0.0f, "play", 255, 255, 255);
    actor_text* quit_button = init_actor_text((640 / 2) - ((3 * 24) / 2), (480 / 2) + 16, 0.0f, "quit", 255, 255, 255);
    dynamic_list_append(s->actors, play_button);
    dynamic_list_append(s_menu->buttons, play_button);
    dynamic_list_append(s->actors, quit_button);
    dynamic_list_append(s_menu->buttons, quit_button);

    return s_menu;
}

void scene_menu_tick(scene* self)
{
    scene_tick(self);

    scene_menu* s_menu = (scene_menu*) self;

    for (int i = 0; i < s_menu->buttons->size; i++)
    {
        actor_text* a_t = (actor_text*) s_menu->buttons->items[i];

        if (s_menu->button_index == i)
        {
            a_t->r = 255.0f;
            a_t->g = 0.0f;
            a_t->b = 0.0f;
        }
        else
        {
            a_t->r = 255.0f;
            a_t->g = 255.0f;
            a_t->b = 255.0f;
        }
    }
}

void scene_menu_draw(scene* self)
{
    scene_draw(self);
}
