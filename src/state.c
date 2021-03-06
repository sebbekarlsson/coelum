#include "include/state.h"
#include "include/actor.h"
#include "include/draw_utils.h"
#include "include/utils.h"
#include "include/matrix.h"
#include "include/component.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string.h>


extern unsigned int SHADER_TEXTURED_SHADED;

/**
 * Initialize a new state_T*
 *
 * @return state_T*
 */
state_T* init_state()
{
    state_T* state = calloc(1, sizeof(struct STATE_STRUCT));
    return state;
}

/**
 * state_T* constructor.
 *
 * @param state_T* state
 * @param int projection_view_width
 * @param int projection_view_height
 * @param unsigned int dimensions
 *
 * @return state_T*
 */
state_T* state_constructor(state_T* state, int projection_view_width, int projection_view_height, unsigned int dimensions)
{
    state->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT*));

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

        // call `tick` on all components within actor.
        for (int j = 0; j < a->components->size; j++)
        {
            component_T* component = (component_T*) a->components->items[j];

            if (component->tick)
                component->tick(component, a);
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

    camera_T* camera = state->camera;

    mat4 final;
    matrix_generate(
        -camera->x,
        -camera->y,
        -camera->z,
        -camera->rx,
        -camera->ry,
        -camera->rz,
        camera->offset_x,
        camera->offset_y,
        camera->offset_z,
        final,
        camera->reverse
    );

    glm_mat4_copy(final, pv->view);
    
    frustum_recalc_geometry(camera->frustum, camera->projection_view->projection, camera->projection_view->view);

    for (int i = 0; i < state->actors->size; i++)
    {
        /**
         * Iterating through each actor in the current state,
         * rotating them, translating them and drawing them.
         */

        actor_T* a = ((actor_T*)state->actors->items[i]);
        actor_draw_default(a, state);

        // call `draw` on all components within actor.
        for (int j = 0; j < a->components->size; j++)
        {
            component_T* component = (component_T*) a->components->items[j];

            if (component->draw)
                component->draw(component, a);
        }

        if (a->draw)
            a->draw(a);

        if (state->lighting_enabled && a->shader_program == SHADER_TEXTURED_SHADED)
            glUniform3fv(glGetUniformLocation(a->shader_program, "world_pos"), 1, (float[]){ a->x, a->y, a->z });  
    }

    camera_unbind(state->camera);

    if (state->lighting_enabled)
    {
        /**
         * If lighting is enabled for the current state,
         * then we fetch all the "light" actors from the current state and
         * push their positions to the shader.
         */

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

int compare(const void *s1, const void *s2)
{
    const actor_T **a = (const actor_T **)s1;
    const actor_T **b = (const actor_T **)s2;
    
    return (*a)->z > (*b)->z;
}

void state_resort_actors(state_T* state)
{
    qsort(state->actors->items, state->actors->size, sizeof(struct ACTOR_STRUCT*), compare);
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
