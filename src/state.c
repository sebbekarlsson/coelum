#include "include/state.h"
#include "include/actor.h"
#include "include/draw_utils.h"
#include "include/utils.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string.h>


extern unsigned int SHADER_TEXTURED_SHADED;

state_T* init_state()
{
    state_T* state = calloc(1, sizeof(struct STATE_STRUCT));
    return state;
}

state_T* state_constructor(state_T* state, int projection_view_width, int projection_view_height, unsigned int dimensions)
{
    state->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));

    glGenVertexArrays(1, &state->VAO);

    state->lighting_enabled = 0;

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
        vec4 qx, qy, qz;
        mat4 mx, my, mz;
        glm_quat(qx, -glm_rad(state->camera->rx), 1.0f, 0.0f, 0.0f);
        glm_quat(qy, -glm_rad(state->camera->ry), 0.0f, 1.0f, 0.0f);
        glm_quat(qz, -glm_rad(state->camera->rz), 0.0f, 0.0f, 1.0f);

        glm_quat_mat4(qx, mx);
        glm_quat_mat4(qy, my);
        glm_quat_mat4(qz, mz);

        mat4 final;

        glm_mat4_mulN((mat4* []){&mx, &my, &mz}, 3, final);

        glm_translate(final, (vec3){ state->camera->x, state->camera->y, state->camera->z });

        glm_mat4_copy(final, pv->view);
    }

    for (int i = 0; i < state->actors->size; i++)
    {
        actor_T* a = ((actor_T*)state->actors->items[i]);

        glUseProgram(a->shader_program);

        send_projection_view_state(a->shader_program, pv);

        vec4 qx, qy, qz;
        mat4 mx, my, mz;

        glm_quat(qx, glm_rad(a->rx), 1.0f, 0.0f, 0.0f);
        glm_quat(qy, glm_rad(a->ry), 0.0f, 1.0f, 0.0f);
        glm_quat(qz, glm_rad(a->rz), 0.0f, 0.0f, 1.0f);

        glm_quat_mat4(qx, mx);
        glm_quat_mat4(qy, my);
        glm_quat_mat4(qz, mz);

        mat4 trans = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1 
        };

        mat4 rot = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        mat4 final;

        glm_mat4_mulN((mat4* []){&mx, &my, &mz}, 3, rot);
        glm_translate(trans, (vec3){ a->x, a->y, a->z });

        glm_mat4_mul(trans, rot, final);

        glm_mat4_copy(final, a->model);
        send_model_state(a->shader_program, a->model);

        if (a->texture)
        {
            glUniform1i(glGetUniformLocation(a->shader_program, "ourTexture"), 0); 

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, a->texture);
        }

        if (state->lighting_enabled && a->shader_program == SHADER_TEXTURED_SHADED)
            glUniform3fv(glGetUniformLocation(a->shader_program, "world_pos"), 1, (float[]){ a->x, a->y, a->z });

        draw_2D_mesh(a->width, a->height, 255.0f, 255.0f, 255.0f, a->VBO, a->EBO);

        if (a->draw)
            a->draw(a);
    }

    camera_unbind(state->camera);

    if (state->lighting_enabled)
    {
        float* light_positions = calloc(1, sizeof(float));
        unsigned int light_positions_size = 0;

        for (int i = 0; i < state->actors->size; i++)
        {
            actor_T* act = (actor_T*) state->actors->items[i];

            if (strcmp(act->type_name, "light") == 0)
            {
                light_positions_size += 3;

                light_positions = realloc(
                    light_positions,
                    (light_positions_size + ( 3 * sizeof(float)))
                );

                light_positions[light_positions_size - 3] = act->x;
                light_positions[light_positions_size - 2] = act->y;
                light_positions[light_positions_size - 1] = act->z; 
            }
        }

        if (light_positions_size)
        {
            glUseProgram(SHADER_TEXTURED_SHADED);

            unsigned uniform_i_number_of_lights = glGetUniformLocation(
                SHADER_TEXTURED_SHADED,
                "number_of_lights"
            );
            glUniform1i(uniform_i_number_of_lights, light_positions_size / 3);
            unsigned uniform_vec3_lightpos = glGetUniformLocation(
                SHADER_TEXTURED_SHADED,
                "light_positions"
            );

            glUniform3fv(uniform_vec3_lightpos, light_positions_size / 3, light_positions);

            free(light_positions);
        }
    }

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
