#include "include/scene.h"
#include "include/actor.h"
#include <string.h>


extern unsigned int SHADER_DEFAULT;

scene* init_scene() {
    scene* s = calloc(1, sizeof(struct SCENE_STRUCT));
    s->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));
    glGenVertexArrays(1, &s->VAO);

    mat4 view = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    mat4 projection = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    memcpy(s->view, view, sizeof(view));
    memcpy(s->projection, projection, sizeof(projection));

    glm_translate(s->view, (vec3){0.0f, 0.0f, 0.0f});
    glm_ortho(0.0f, 640.0f, 0.0f, 480.0f, 0.0f, 1.5f, s->projection);

    dynamic_list_append(s->actors, init_actor(0.0f, 0.0f, 0.0f));
    dynamic_list_append(s->actors, init_actor(128.0f, 128.0f, 0.0f));

    return s;
}

void scene_tick(scene* s) {
    for (int i = 0; i < s->actors->size; i++) {
        actor_tick((actor*)s->actors->items[i]);
    }
}

void scene_draw(scene* s) {
    glBindVertexArray(s->VAO);

    unsigned uniform_mat4_model = glGetUniformLocation(SHADER_DEFAULT, "model");
    unsigned uniform_mat4_view = glGetUniformLocation(SHADER_DEFAULT, "view");
    unsigned uniform_mat4_projection = glGetUniformLocation(SHADER_DEFAULT, "projection");

    glUniformMatrix4fv(uniform_mat4_projection, 1, GL_FALSE, (float *) s->projection);
    glUniformMatrix4fv(uniform_mat4_view, 1, GL_FALSE, (float *) s->view);

    for (int i = 0; i < s->actors->size; i++) {
        actor* a = ((actor*)s->actors->items[i]);

        glm_translate(a->model, (vec3){a->x, a->y, a->z});
        glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) a->model);

        draw_actor(a);

        glm_translate(a->model, (vec3){-a->x, -a->y, -a->z});
        glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) a->model);
    }
}
