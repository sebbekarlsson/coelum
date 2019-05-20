#include "include/scene.h"
#include "include/actor.h"
#include "include/render.h"
#include <string.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


extern unsigned int SHADER_DEFAULT;

/**
 * Creates a new scene.
 * (This function is abstract and should not be used)
 *
 * @return scene_T*
 */
scene_T* init_scene()
{
    scene_T* s = calloc(1, sizeof(struct SCENE_STRUCT)); 

    return s;
}

/**
 * Scene constructor, structs that inherit from scene should use this in their
 * initialization method.
 *
 * @param scene_T* s
 *
 * @return scene_T*
 */
scene_T* scene_constructor(scene_T* scene,  void (*tick)(scene_T* self), void (*draw)(scene_T* self))
{
    scene->tick = tick;
    scene->draw = draw;

    scene->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));
    glGenVertexArrays(1, &scene->VAO);

    scene->camera = init_camera();
}

/**
 * Default scene tick method.
 * This method calls tick on all child actors.
 *
 * @param scene_T* s
 */
void scene_tick(scene_T* scene)
{
    for (int i = 0; i < scene->actors->size; i++)
    {
        actor_T* a = (actor_T*)scene->actors->items[i];

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
 * @param scene_T* scene
 */
void scene_draw(scene_T* scene)
{

    projection_view_T* pv = scene->camera->projection_view;

    glBindVertexArray(scene->VAO);

    camera_bind(scene->camera);

    for (int i = 0; i < scene->actors->size; i++)
    {
        actor_T* a = ((actor_T*)scene->actors->items[i]);

        if (a->draw)
        {
            glUseProgram(a->shader_program);

            send_projection_view_state(a->shader_program, pv);

            glUniformMatrix4fv(pv->uniform_mat4_projection, 1, GL_FALSE, (float *) pv->projection);
            glUniformMatrix4fv(pv->uniform_mat4_view, 1, GL_FALSE, (float *) pv->view);

            glm_translate(a->model, (vec3){a->x, a->y, a->z});
            glUniformMatrix4fv(scene->uniform_mat4_model, 1, GL_FALSE, (float *) a->model);

            if (a->texture)
            {
                glUniform1i(glGetUniformLocation(a->shader_program, "ourTexture"), 0); 
            }

            a->draw(a);

            glm_translate(a->model, (vec3){-a->x, -a->y, -a->z});
            glUniformMatrix4fv(scene->uniform_mat4_model, 1, GL_FALSE, (float *) a->model);
        }
    }

    camera_unbind(scene->camera);

    glBindVertexArray(0);
}
