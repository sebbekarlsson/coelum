#include "include/scene_manager.h"


scene_manager* init_scene_manager() {
    scene_manager* sm = calloc(1, sizeof(struct SCENE_MANAGER_STRUCT));
    sm->scenes = init_dynamic_list(sizeof(struct SCENE_STRUCT));
    sm->scene_index = 0;

    return sm;
}

scene* get_current_scene_scene_manager(scene_manager* sm) {
    return (scene*) sm->scenes->items[sm->scene_index];
}

void append_scene_scene_manager(scene_manager* sm, scene* s) {
    append_dynamic_list(sm->scenes, s);
}
