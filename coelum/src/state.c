#include "include/state.h"
#include "include/actor.h"
#include "include/draw_utils.h"
#include "include/utils.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string.h>


state_T* init_state()
{
    state_T* state = calloc(1, sizeof(struct STATE_STRUCT));
    return state;
}

state_T* state_constructor(state_T* state, int projection_view_width, int projection_view_height, unsigned int dimensions)
{
    state->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));

    glGenVertexArrays(1, &state->VAO);

    state->camera = init_camera(projection_view_width, projection_view_height, dimensions);

    return state;
}


/**
 * Default state tick method.
 * Calls `tick` on every actor bound to the state.
 *
 * @param state_T* state
 */
void state_tick(state_T* state)
{
    for (int i = 0; i < state->actors->size; i++)
    {
        actor_T* a = (actor_T*)state->actors->items[i];

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
 * Default state draw method.
 * Draws all actors that are bound to the state.
 *
 * @param state_T* state
 */
void state_draw(state_T* state)
{
    projection_view_T* pv = state->camera->projection_view;

    glBindVertexArray(state->VAO); 


    if (pv->dimensions == 2)
    { // we are doing 2D
        camera_bind(state->camera);
    }
    else
    { // we are doing 3D
        mat4 rot = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        mat4 pos = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        mat4 final = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        // rotation
        glm_rotate(rot, -to_radians(state->camera->rx), (vec3){ 1.0f, 0.0f, 0.0f });
        glm_rotate(rot, -to_radians(state->camera->ry), (vec3){ 0.0f, 1.0f, 0.0f });
        glm_rotate(rot, -to_radians(state->camera->rz), (vec3){ 0.0f, 0.0f, 1.0f });

        // position
        glm_translate(pos, (vec3){state->camera->x, state->camera->y, state->camera->z});

        glm_mat4_mul(rot, pos, final);
        glm_mat4_copy(final, state->camera->projection_view->view);
    }

    for (int i = 0; i < state->actors->size; i++)
    {
        actor_T* a = ((actor_T*)state->actors->items[i]);

        glUseProgram(a->shader_program);

        send_projection_view_state(a->shader_program, pv);

        mat4 arot = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        mat4 apos = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }; 

        mat4 afinal = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }; 

        // rotation
        glm_rotate(arot, -to_radians(a->rx), (vec3){ 1.0f, 0.0f, 0.0f });
        glm_rotate(arot, to_radians(a->ry), (vec3){ 0.0f, 1.0f, 0.0f });
        glm_rotate(arot, to_radians(a->rz), (vec3){ 0.0f, 0.0f, 1.0f });
        
        // position
        glm_translate(apos, (vec3){a->x, a->y, a->z});
        
        glm_mat4_mul(apos, arot, afinal);
        glm_mat4_copy(afinal, a->model);
        send_model_state(a->shader_program, a->model);

        if (a->texture)
        {
            glUniform1i(glGetUniformLocation(a->shader_program, "ourTexture"), 0); 

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, a->texture);
        }

        draw_2D_mesh(a->width, a->height, 255.0f, 255.0f, 255.0f, a->VBO, a->EBO);

        if (a->draw)
            a->draw(a);

        send_model_state(a->shader_program, a->model);
    }

    camera_unbind(state->camera); 

    glBindVertexArray(0);
}

/**
 * Deallocation function for `state` object.
 *
 * @param state_T* state
 */
void state_free(state_T* state)
{
    glDeleteBuffers(1, &state->VAO);
    
    for (int i = 0; i < state->actors->size; i++)
        actor_free((actor_T*) state->actors->items[i]);

    free(state->actors);
    camera_free(state->camera);

    free(state);
}
