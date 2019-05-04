#include "include/actor.h"
#include "include/scene_manager.h"
#include "include/shader_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 64

extern shader_manager* SHADER_MANAGER;
extern scene_manager* SCENE_MANAGER;

extern unsigned int SHADER_DEFAULT;

float VERTICES_DEFAULT[] =
{
    SIZE,  SIZE, 0.0f,  // top right
    SIZE, -SIZE, 0.0f,  // bottom right
    -SIZE, -SIZE, 0.0f,  // bottom left
    -SIZE,  SIZE, 0.0f   // top left 
};

float VERTICES_TEXTURED[] =
{
    // positions          // colors           // texture coords
     SIZE,  SIZE, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     SIZE, -SIZE, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -SIZE, -SIZE, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -SIZE,  SIZE, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

unsigned int INDICES_DEFAULT [] =
{
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

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
    a->x = x;
    a->y = y;
    a->z = z; 

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
    glBindBuffer(GL_ARRAY_BUFFER, a->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES_TEXTURED), VERTICES_TEXTURED, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES_DEFAULT), INDICES_DEFAULT, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // texcoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glUseProgram(SHADER_DEFAULT);
    // glBindVertexArray(scene_manager_get_current_scene(SCENE_MANAGER)->VAO);

    if (a->texture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, a->texture);
        glBindVertexArray(scene_manager_get_current_scene(SCENE_MANAGER)->VAO);
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}
