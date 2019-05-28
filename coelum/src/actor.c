#include "include/actor.h"
#include "include/theatre.h"
#include "include/draw_utils.h"
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
actor_T* init_actor(float x, float y, float z)
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
 * Currently draws the actor->texture if it exists.
 *
 * @param actor_T* actor
 */
void actor_draw(actor_T* actor)
{
    state_T* state = (state_T*) scene_manager_get_current_scene(THEATRE->scene_manager);
    if (actor->texture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, actor->texture);
        glBindVertexArray(state->VAO);
    }

    draw_2D_mesh(actor->width, actor->height, 255.0f, 255.0f, 255.0f, actor->VBO, actor->EBO);
}

/**
 * Push an actor in an angle
 *
 * @param actor_T* self
 * @param float angle
 * @param float acceleration
 */
void actor_push(actor_T* self, float angle, float acceleration)
{
    float radians = angle * (GLM_PI / 180.0f);

    self->dx += cos(radians) * acceleration;
    self->dy -= sin(radians) * acceleration;
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
}
