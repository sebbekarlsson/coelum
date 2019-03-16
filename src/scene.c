#include "include/scene.h"
#include "include/actor.h"


scene* init_scene() {
    scene* s = calloc(1, sizeof(struct SCENE_STRUCT));
    s->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));

    return s;
}

void tick_scene(scene* s) {
    for (int i = 0; i < s->actors->size; i++) {
        tick_actor((actor*)s->actors->items[i]);
    }
}

void draw_scene(scene* s) {
    for (int i = 0; i < s->actors->size; i++) {
        draw_actor((actor*)s->actors->items[i]);
    }
}
