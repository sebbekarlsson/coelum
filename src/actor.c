#include "include/actor.h"
#include "include/scene_manager.h"
#include "include/shader_manager.h"
#include "include/render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define SIZE 16

#define PI 3.14159265

extern shader_manager* SHADER_MANAGER;
extern scene_manager* SCENE_MANAGER;

extern unsigned int SHADER_TEXTURED;

/**
 * Initializes an actor, note that this method is sort of abstract and should
 * not really be used.
 *
 * @param float x
 * @param float y
 * @param float z
 *
 * @return actor*
 */
actor* init_actor(float x, float y, float z)
{
    return (actor*) calloc(1, sizeof(struct ACTOR_STRUCT));
}

/**
 * Actor constructor, structs that inherit from actor should use this in their
 * initialization method.
 *
 * @param actor* a
 * @param float x
 * @param float y
 * @param float z
 */
actor* actor_constructor(
    actor* a,
    float x,
    float y,
    float z,
    void (*tick)(actor* self),
    void (*draw)(actor* self)
)
{
    a->type = -1;
    a->x = x;
    a->y = y;
    a->z = z;
    a->dx = 0.0f;
    a->dy = 0.0f;
    a->dz = 0.0f;
    a->friction = 0.0f;
    a->width = 1;
    a->height = 1;

    a->loaded = 0;

    glGenBuffers(1, &a->VBO);
    glGenBuffers(1, &a->EBO);

    mat4 model =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    memcpy(a->model, model, sizeof(model));

    a->shader_program = SHADER_TEXTURED;
    a->tick = tick;
    a->draw = draw;

    return a;
}

/**
 * Default actor tick method
 *
 * @param actor* a
 */
void actor_tick(actor* a)
{
    // silence
}

/**
 * Default actor draw method.
 * Currently draws the actor->texture if it exists.
 *
 * @param actor* a
 */
void actor_draw(actor* a)
{
    if (a->texture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, a->texture);
        glBindVertexArray(scene_manager_get_current_scene(SCENE_MANAGER)->VAO);
    }

    render_2D_mesh(a->width, a->height, 255.0f, 255.0f, 255.0f, a->VBO, a->EBO);
}

void actor_push(actor* self, float angle, float acceleration)
{
    float radians = angle * (PI / 180.0f);

    self->dx += cos(radians) * acceleration;
    self->dy -= sin(radians) * acceleration;
}
