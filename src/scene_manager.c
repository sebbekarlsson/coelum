#include "include/scene_manager.h"


#define MIN(a,b) (((a)<(b))?(a):(b))

/**
 * Creates a new scene_manager.
 *
 * @return scene_manager_T*
 */
scene_manager_T* init_scene_manager()
{
    scene_manager_T* scene_manager = calloc(1, sizeof(struct SCENE_MANAGER_STRUCT));
    scene_manager->scenes = init_dynamic_list(sizeof(struct SCENE_STRUCT));
    scene_manager->scene_index = -1;

    return scene_manager;
}

/**
 * Use this to get the current scene.
 * The current scene is based on the scene_manager's scene_index
 *
 * @param scene_manager_T* scene_manager
 *
 * @return scene_T*
 */
scene_T* scene_manager_get_current_scene(scene_manager_T* scene_manager)
{
    return (scene_T*) scene_manager->scenes->items[scene_manager->scene_index];
}

/**
 * Use this to register a new scene to a scene_manager.
 *
 * @param scene_manager_T* scene_manager
 * @param scene_T* s
 */
void scene_manager_register_scene(scene_manager_T* scene_manager, scene_T* s)
{
    dynamic_list_append(scene_manager->scenes, s);
}

/**
 * Updates the current scene
 *
 * @param scene_manager_T* scene_manager
 */
void scene_manager_tick(scene_manager_T* scene_manager)
{
    scene_T* s = scene_manager_get_current_scene(scene_manager);
    s->tick(s);
}

/**
 * Draws the current scene
 *
 * @param scene_manager_T* scene_manager
 */
void scene_manager_draw(scene_manager_T* scene_manager)
{
    scene_T* s = scene_manager_get_current_scene(scene_manager);
    s->draw(s);
}

/**
 * Use this to move to the next scene.
 * This method basically just increases the scene_index.
 *
 * @param scene_manager_T* scene_manager
 */
void scene_manager_next(scene_manager_T* scene_manager)
{

    if (scene_manager->scene_index != -1)
    {
        scene_T* p_scene = scene_manager_get_current_scene(scene_manager);

        if (p_scene->unload)
            p_scene->unload(p_scene);
    }

    scene_manager->scene_index = MIN(scene_manager->scene_index + 1, scene_manager->scenes->size - 1);

    scene_T* n_scene = scene_manager_get_current_scene(scene_manager);

    if (n_scene->load)
        n_scene->load(n_scene);
}
