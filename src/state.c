#include "include/state.h"
#include "include/actor.h"
#include "include/draw_utils.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


state_T* init_state()
{
    state_T* state = calloc(1, sizeof(struct STATE_STRUCT));
    return state;
}

state_T* state_constructor(state_T* state, void (*tick)(state_T* self), void (*draw)(state_T* self), int projection_view_width, int projection_view_height)
{
    state->tick = tick;
    state->draw = draw;
    state->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT));

    glGenVertexArrays(1, &state->VAO);

    state->camera = init_camera(projection_view_width, projection_view_height);

    return state;
}


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

void state_draw(state_T* state)
{
    projection_view_T* pv = state->camera->projection_view;

    glBindVertexArray(state->VAO);

    camera_bind(state->camera);

    for (int i = 0; i < state->actors->size; i++)
    {
        actor_T* a = ((actor_T*)state->actors->items[i]);

        if (a->draw)
        {
            glUseProgram(a->shader_program);

            send_projection_view_state(a->shader_program, pv);

            glm_translate(a->model, (vec3){a->x, a->y, a->z});
            send_model_state(a->shader_program, a->model);

            if (a->texture)
            {
                glUniform1i(glGetUniformLocation(a->shader_program, "ourTexture"), 0); 
            }

            a->draw(a);

            glm_translate(a->model, (vec3){-a->x, -a->y, -a->z});
            send_model_state(a->shader_program, a->model);
        }
    }

    camera_unbind(state->camera);

    glBindVertexArray(0);
}

void state_free(state_T* state)
{
    glDeleteBuffers(1, &state->VAO);
    
    for (int i = 0; i < state->actors->size; i++)
        actor_free((actor_T*) state->actors->items[i]);

    free(state->actors);
    camera_free(state->camera);

    free(state);
}
