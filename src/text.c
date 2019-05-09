#include "include/text.h"
#include "include/scene_manager.h"
#include <string.h>
#include <cglm/cglm.h>
#include <cglm/call.h>


extern scene_manager* SCENE_MANAGER;

extern unsigned int SHADER_DEFAULT;
extern texture_t* TEXTURE_DEFAULT_FONT;

/**
 * Used to render a text at a specific position.
 *
 * @param const char* text
 * @param float x
 * @param float y
 * @param float z
 */
void render_text(const char* text, float x, float y, float z, float r, float g, float b)
{
    int size = 6;
    int spacing = 0;

    float d_r = r / 255.0f;
    float d_g = g / 255.0f;
    float d_b = b / 255.0f;

    float vertices[] = 
    {
        // positions          // colors           // texture coords
        size,  size, 0.0f,   r, g, b,   1.0f, 1.0f,   // top right
        size, -size, 0.0f,   r, g, b,   1.0f, 0.0f,   // bottom right
        -size, -size, 0.0f,   r, g, b,   0.0f, 0.0f,   // bottom left
        -size,  size, 0.0f,   r, g, b,   0.0f, 1.0f    // top left
    };

    unsigned int indices [] =
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];

        unsigned int EBO;

        glGenBuffers(1, &EBO);

        mat4 model =
        {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        
        glm_translate(model, (vec3){x, y, z});

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
        unsigned int tex = get_char_texture_from_texture(c, 7, 7, 8, 12, TEXTURE_DEFAULT_FONT);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(glGetUniformLocation(SHADER_DEFAULT, "ourTexture"), 0); 
        glBindVertexArray(scene_manager_get_current_scene(SCENE_MANAGER)->VAO);
        
        unsigned uniform_mat4_model = glGetUniformLocation(SHADER_DEFAULT, "model");
        glm_translate(model, (vec3){(i * (24 + spacing)), 0, 0});
        glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);
        glDeleteBuffers(1, &EBO);
        glDeleteTextures(1, &tex);
    }

    glDeleteBuffers(1, &VBO);
}
