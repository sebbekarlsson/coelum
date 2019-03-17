#include "include/scene_manager.h"


scene_manager* init_scene_manager() {
    scene_manager* sm = calloc(1, sizeof(struct SCENE_MANAGER_STRUCT));
    sm->scenes = init_dynamic_list(sizeof(struct SCENE_STRUCT));
    sm->scene_index = 0;

    return sm;
}

scene* scene_manager_get_current_scene(scene_manager* sm) {
    return (scene*) sm->scenes->items[sm->scene_index];
}

void scene_manager_register_scene(scene_manager* sm, scene* s) {
    dynamic_list_append(sm->scenes, s);
}

void scene_manager_tick(scene_manager* sm) {
    scene_tick(scene_manager_get_current_scene(sm));
}

void scene_manager_draw(scene_manager* sm) {
    scene_draw(scene_manager_get_current_scene(sm));
}
