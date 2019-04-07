#include "include/actor.h"
#include "include/scene_manager.h"
#include "include/shader_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 32

extern shader_manager* SHADER_MANAGER;
extern scene_manager* SCENE_MANAGER;

extern unsigned int SHADER_DEFAULT;


float VERTICES_DEFAULT[] = {
    SIZE,  SIZE, 0.0f,  // top right
    SIZE, -SIZE, 0.0f,  // bottom right
    -SIZE, -SIZE, 0.0f,  // bottom left
    -SIZE,  SIZE, 0.0f   // top left 
};

float VERTICES_TEXTURED[] = {
    // positions          // colors           // texture coords
    /* SIZE,  SIZE, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     SIZE, -SIZE, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -SIZE, -SIZE, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -SIZE,  SIZE, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left  */
    // positions          // colors           // texture coords
     SIZE,  SIZE, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     SIZE, -SIZE, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -SIZE, -SIZE, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -SIZE,  SIZE, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

unsigned int INDICES_DEFAULT [] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

actor* init_actor(float x, float y, float z) {
    actor* a = calloc(1, sizeof(struct ACTOR_STRUCT));
    // actor_constructor(a, x, y, z);
    
    return a;
}

actor* actor_constructor(actor* a, float x, float y, float z, void (*tick)(actor* self), void (*draw)(actor* self)) {
    a->x = x;
    a->y = y;
    a->z = z; 

    glGenBuffers(1, &a->VBO);
    glGenBuffers(1, &a->EBO);

    mat4 model = {
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

void actor_tick(actor* a) {
    // printf("Tick actor!\n");
    a->x += 0.5;
    a->y += 0.5;
}

void actor_draw(actor* a) {
    // printf("Draw actor!\n"); 

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

    if (a->texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, a->texture);
        glBindVertexArray(scene_manager_get_current_scene(SCENE_MANAGER)->VAO);
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}
