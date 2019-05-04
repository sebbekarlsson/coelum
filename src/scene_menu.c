#include "include/scene_menu.h"
#include "include/actor_pad.h"
#include "include/actor_text.h"
#include "include/input.h"
#include "include/scene_manager.h"


extern scene_manager* SCENE_MANAGER;
extern event_manager* EVENT_MANAGER;

/**
 * Called when the enter key is pressed or released.
 *
 * @param int state
 */
void scene_menu_key_enter_callback(int state)
{
    if (state)
        scene_manager_next(SCENE_MANAGER);
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
    scene_constructor(s);
    
    add_event_listener(EVENT_MANAGER, GLFW_KEY_ENTER, scene_menu_key_enter_callback);

    dynamic_list_append(s->actors, init_actor_text(128, 128, 0.0f, "play"));

    return s_menu;
}

void scene_menu_tick(scene* self)
{
    scene_tick(self);
}

void scene_menu_draw(scene* self)
{
    scene_draw(self);
}
