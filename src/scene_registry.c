#include "include/scene_registry.h"
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

    scene_manager_register_scene(sm, init_scene());
}
