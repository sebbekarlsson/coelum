#include "include/actor.h"
#include "include/scene_manager.h"
#include "include/shader_manager.h"
#include <stdio.h>
#include <stdlib.h>


extern shader_manager* SHADER_MANAGER;
extern scene_manager* SCENE_MANAGER;

extern unsigned int SHADER_DEFAULT;

float VERTICES_DEFAULT[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

unsigned int INDICES_DEFAULT [] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

actor* init_actor(float x, float y, float z) {
    actor* a = calloc(1, sizeof(struct ACTOR_STRUCT));
    a->x = x;
    a->y = y;
    a->z = z; 

    glGenBuffers(1, &a->VBO);
    glGenBuffers(1, &a->EBO);

    return a;
}

void actor_tick(actor* a) {
    // printf("Tick actor!\n");
}

void draw_actor(actor* a) {
    // printf("Draw actor!\n"); 

    glBindBuffer(GL_ARRAY_BUFFER, a->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES_DEFAULT), VERTICES_DEFAULT, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES_DEFAULT), INDICES_DEFAULT, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(SHADER_DEFAULT);
    glBindVertexArray(scene_manager_get_current_scene(SCENE_MANAGER)->VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
