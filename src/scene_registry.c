#include "include/scene_registry.h"
#include "include/scene_menu.h"
#include "include/scene_play.h"
#include <stdio.h>

/**
 * All scenes go here
 */
void register_scenes(scene_manager* sm) {
    printf("Registering scenes...\n");
    /* TODO:
     * - register main menu scene
     * - register actual game scene
     */

    scene_manager_register_scene(sm, (scene*) init_scene_menu());
    scene_manager_register_scene(sm, (scene*) init_scene_play());
}
