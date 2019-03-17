#include "include/scene.h"
#include "include/actor.h"


scene* init_scene() {
    scene* s = calloc(1, sizeof(struct SCENE_STRUCT));
    s->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));
    glGenVertexArrays(1, &s->VAO);

    dynamic_list_append(s->actors, init_actor(0.0f, 0.0f, 0.0f));

    return s;
}

void scene_tick(scene* s) {
    for (int i = 0; i < s->actors->size; i++) {
        actor_tick((actor*)s->actors->items[i]);
    }
}

void scene_draw(scene* s) {
    glBindVertexArray(s->VAO);
    for (int i = 0; i < s->actors->size; i++) {
        draw_actor((actor*)s->actors->items[i]);
    }
}
