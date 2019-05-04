#include "include/text.h"
#include "include/scene_manager.h"
#include <string.h>
#include <cglm/cglm.h>
#include <cglm/call.h>


#define CHAR_WIDTH 7
#define CHAR_HEIGHT 7

extern scene_manager* SCENE_MANAGER;

extern unsigned int SHADER_DEFAULT;


void render_text(const char* text, float x, float y, float z) {
    texture_t* font_texture = get_texture("res/font/null_terminator.png");

    int size = 24;
    int spacing = 12;

    float vertices[] = {
        // positions          // colors           // texture coords
        size,  size, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        size, -size, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -size, -size, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -size,  size, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices [] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    for (int i = 0; i < strlen(text); i++) {
        char c = text[i];

        unsigned int VBO;
        unsigned int EBO;

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        mat4 model = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        
        glm_translate(model, (vec3){x, y, z});

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

        glActiveTexture(GL_TEXTURE0);
        unsigned int tex = get_char_texture_from_texture(c, 7, 7, 8, 12, font_texture);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(glGetUniformLocation(SHADER_DEFAULT, "ourTexture"), 0); 
        glBindVertexArray(scene_manager_get_current_scene(SCENE_MANAGER)->VAO);
        
        unsigned uniform_mat4_model = glGetUniformLocation(SHADER_DEFAULT, "model");
        glm_translate(model, (vec3){(i * ((24 * 2) + spacing)), 0, 0});
        glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);
    }
}
