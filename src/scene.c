#include "include/scene.h"
#include "include/actor.h"
#include <string.h>


extern unsigned int SHADER_DEFAULT;

/**
 * Creates a new scene.
 * (This function is abstract and should not be used)
 *
 * @return scene*
 */
scene* init_scene()
{
    scene* s = calloc(1, sizeof(struct SCENE_STRUCT)); 

    return s;
}

/**
 * Scene constructor, structs that inherit from scene should use this in their
 * initialization method.
 *
 * @param scene* s
 *
 * @return scene*
 */
scene* scene_constructor(scene* s,  void (*tick)(scene* self), void (*draw)(scene* self))
{
    s->tick = tick;
    s->draw = draw;

    s->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));
    glGenVertexArrays(1, &s->VAO);

    mat4 view =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    mat4 projection =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    memcpy(s->view, view, sizeof(view));
    memcpy(s->projection, projection, sizeof(projection));

    glm_translate(s->view, (vec3){0.0f, 0.0f, 0.0f});
    glm_ortho(0.0f, 640, 480, 0.0f, 0.0f, 1.5f, s->projection);  
}

/**
 * Default scene tick method.
 * This method calls tick on all child actors.
 *
 * @param scene* s
 */
void scene_tick(scene* s)
{
    for (int i = 0; i < s->actors->size; i++)
    {
        actor* a = (actor*)s->actors->items[i];

        if (!a->loaded)
        {
            if (a->load)
            {
                a->load(a);
                a->loaded = 1;
            }
        }
        
        if (a->tick)
            a->tick(a);
    }
}

/**
 * Default scene draw method.
 * This method draws all child actors.
 *
 * @param scene* s
 */
void scene_draw(scene* s)
{
    glBindVertexArray(s->VAO);

    if (!s->uniform_mat4_model)
        s->uniform_mat4_model = glGetUniformLocation(SHADER_DEFAULT, "model");

    if (!s->uniform_mat4_view)
        s->uniform_mat4_view = glGetUniformLocation(SHADER_DEFAULT, "view");

    if (!s->uniform_mat4_projection)
        s->uniform_mat4_projection = glGetUniformLocation(SHADER_DEFAULT, "projection");

    glUniformMatrix4fv(s->uniform_mat4_projection, 1, GL_FALSE, (float *) s->projection);
    glUniformMatrix4fv(s->uniform_mat4_view, 1, GL_FALSE, (float *) s->view);

    for (int i = 0; i < s->actors->size; i++)
    {
        actor* a = ((actor*)s->actors->items[i]);

        if (a->draw)
        {
            glm_translate(a->model, (vec3){a->x, a->y, a->z});
            glUniformMatrix4fv(s->uniform_mat4_model, 1, GL_FALSE, (float *) a->model);

            if (a->texture)
            {
                glUniform1i(glGetUniformLocation(SHADER_DEFAULT, "ourTexture"), 0); 
            }

            a->draw(a);

            glm_translate(a->model, (vec3){-a->x, -a->y, -a->z});
            glUniformMatrix4fv(s->uniform_mat4_model, 1, GL_FALSE, (float *) a->model);
        }
    }

    glBindVertexArray(0);
}
