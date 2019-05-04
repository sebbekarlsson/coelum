#include "include/scene_play.h"
#include "include/actor_pad.h"
#include "include/actor_text.h"


scene_play* init_scene_play() {
    scene_play* s_play = calloc(1, sizeof(struct SCENE_PLAY_STRUCT));
    scene* s = (scene*) s_play;
    scene_constructor(s);

    dynamic_list_append(s->actors, init_actor_pad(64.0f * 2, 0.0f, 0.0f));

    return s_play;
}

void scene_play_tick(scene* self) {
    scene_tick(self);
}

void scene_play_draw(scene* self) {
    scene_draw(self);
}
