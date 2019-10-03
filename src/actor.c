#include "include/actor.h"
#include "include/theatre.h"
#include "include/draw_utils.h"
#include "include/physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cglm/types.h>
#include <glad/glad.h> 


extern theatre_T* THEATRE;

extern unsigned int SHADER_TEXTURED;

/**
 * Initializes an actor, note that this method is sort of abstract and should
 * not really be used.
 *
 * @param float x
 * @param float y
 * @param float z
 *
 * @return actor_T*
 */
actor_T* init_actor()
{
    return (actor_T*) calloc(1, sizeof(struct ACTOR_STRUCT));
}

/**
 * Actor constructor, structs that inherit from actor should use this in their
 * initialization method.
 *
 * @param actor_T* actor
 * @param float x
 * @param float y
 * @param float z
 */
actor_T* actor_constructor(
    actor_T* actor,
    float x,
    float y,
    float z,
    void (*tick)(actor_T* self),
    void (*draw)(actor_T* self),
    const char* type_name
)
{
    actor->x = x;
    actor->y = y;
    actor->z = z;
    actor->dx = 0.0f;
    actor->dy = 0.0f;
    actor->dz = 0.0f;
    actor->rx = 0.0f;
    actor->ry = 0.0f;
    actor->rz = 0.0f;
    actor->friction = 0.0f;
    actor->width = 1;
    actor->height = 1;
    actor->depth = 1;

    actor->loaded = 0;

    glGenBuffers(1, &actor->VBO);
    glGenBuffers(1, &actor->EBO);

    mat4 model =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    memcpy(actor->model, model, sizeof(model));

    actor->shader_program = SHADER_TEXTURED;
    actor->tick = tick;
    actor->draw = draw;
    actor->type_name = type_name;
    actor->sprite = (void*) 0;

    return actor;
}

/**
 * Default actor tick method
 *
 * @param actor_T* actor
 */
void actor_tick(actor_T* actor)
{
    // silence
}

/**
 * Default actor draw method.
 *
 * @param actor_T* actor
 */
void actor_draw(actor_T* actor)
{
    // silence
}

void actor_draw_default(actor_T* self, state_T* state)
{
    projection_view_T* pv = state->camera->projection_view;

    /**
     * NOTE: only the model in the shader program on the actor is
     * being automatically positioned.
     * TODO: make this better.
     */
    glUseProgram(self->shader_program);

    send_projection_view_state(self->shader_program, pv);

    vec4 qx, qy, qz;
    mat4 mx, my, mz;

    glm_quat(qx, glm_rad(self->rx), 1.0f, 0.0f, 0.0f);
    glm_quat(qy, glm_rad(self->ry), 0.0f, 1.0f, 0.0f);
    glm_quat(qz, glm_rad(self->rz), 0.0f, 0.0f, 1.0f);

    glm_quat_mat4(qx, mx);
    glm_quat_mat4(qy, my);
    glm_quat_mat4(qz, mz);

    mat4 trans = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 
    };

    mat4 trans_two = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 
    };

    mat4 trans_fuck = {
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

    glm_translate(trans, (vec3){ self->x+(self->width/2), self->y+(self->height/2), self->z });
    glm_translate(trans_two, (vec3){ -(self->x + (self->width/2)), -(self->y + self->height/2), self->z });
    glm_translate(trans_fuck, (vec3){ self->x, self->y, self->z });

    glm_mat4_mulN((mat4* []){&trans, &rot, &trans_two, &trans_fuck}, 4, final);

    glm_mat4_copy(final, self->model);
    send_model_state(self->shader_program, self->model);

    if (self->sprite != (void*) 0)
    {
        sprite_draw(self->sprite, state);
    }
}

/**
 * Deallocate function for `actor` object.
 *
 * @param actor_T* actor
 */
void actor_free(actor_T* actor)
{
    glDeleteBuffers(1, &actor->VBO);
    glDeleteBuffers(1, &actor->EBO);

    if (actor->sprite)
        sprite_free(actor->sprite);
}
