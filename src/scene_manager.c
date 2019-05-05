#include "include/scene_manager.h"


#define MIN(a,b) (((a)<(b))?(a):(b))

/**
 * Creates a new scene_manager.
 *
 * @return scene_manager*
 */
scene_manager* init_scene_manager()
{
    scene_manager* sm = calloc(1, sizeof(struct SCENE_MANAGER_STRUCT));
    sm->scenes = init_dynamic_list(sizeof(struct SCENE_STRUCT));
    sm->scene_index = -1;

    return sm;
}

/**
 * Use this to get the current scene.
 * The current scene is based on the scene_manager's scene_index
 *
 * @param scene_manager* sm
 *
 * @return scene*
 */
scene* scene_manager_get_current_scene(scene_manager* sm)
{
    return (scene*) sm->scenes->items[sm->scene_index];
}

/**
 * Use this to register a new scene to a scene_manager.
 *
 * @param scene_manager* sm
 * @param scene* s
 */
void scene_manager_register_scene(scene_manager* sm, scene* s)
{
    dynamic_list_append(sm->scenes, s);
}

/**
 * Updates the current scene
 *
 * @param scene_manager* sm
 */
void scene_manager_tick(scene_manager* sm)
{
    scene* s = scene_manager_get_current_scene(sm);
    s->tick(s);
}

/**
 * Draws the current scene
 *
 * @param scene_manager* sm
 */
void scene_manager_draw(scene_manager* sm)
{
    scene* s = scene_manager_get_current_scene(sm);
    s->draw(s);
}

/**
 * Use this to move to the next scene.
 * This method basically just increases the scene_index.
 *
 * @param scene_manager* sm
 */
void scene_manager_next(scene_manager* sm)
{

    if (sm->scene_index != -1)
    {
        scene* p_scene = scene_manager_get_current_scene(sm);

        if (p_scene->unload)
            p_scene->unload(p_scene);
    }

    sm->scene_index = MIN(sm->scene_index + 1, sm->scenes->size - 1);

    scene* n_scene = scene_manager_get_current_scene(sm);

    if (n_scene->load)
        n_scene->load(n_scene);
}
