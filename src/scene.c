#include "include/scene.h"
#include "include/actor.h"
#include <string.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


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

    s->pv = init_projection_view();
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

    projection_view* pv = s->pv;

    glBindVertexArray(s->VAO);

    for (int i = 0; i < s->actors->size; i++)
    {
        actor* a = ((actor*)s->actors->items[i]);

        if (a->draw)
        {
            glUseProgram(a->shader_program);
            if (!s->uniform_mat4_model)
                s->uniform_mat4_model = glGetUniformLocation(a->shader_program, "model");

            if (!pv->uniform_mat4_view)
                pv->uniform_mat4_view = glGetUniformLocation(a->shader_program, "view");

            if (!pv->uniform_mat4_projection)
                pv->uniform_mat4_projection = glGetUniformLocation(a->shader_program, "projection");

            glUniformMatrix4fv(pv->uniform_mat4_projection, 1, GL_FALSE, (float *) pv->projection);
            glUniformMatrix4fv(pv->uniform_mat4_view, 1, GL_FALSE, (float *) pv->view);

            glm_translate(a->model, (vec3){a->x, a->y, a->z});
            glUniformMatrix4fv(s->uniform_mat4_model, 1, GL_FALSE, (float *) a->model);

            if (a->texture)
            {
                glUniform1i(glGetUniformLocation(a->shader_program, "ourTexture"), 0); 
            }

            a->draw(a);

            glm_translate(a->model, (vec3){-a->x, -a->y, -a->z});
            glUniformMatrix4fv(s->uniform_mat4_model, 1, GL_FALSE, (float *) a->model);
        }
    }

    glBindVertexArray(0);
}
