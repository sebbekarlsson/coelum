#include "include/draw_utils.h"
#include "include/shader_registry.h"
#include "include/textures.h"
#include <string.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


extern unsigned int SHADER_COLORED;
extern unsigned int SHADER_TEXTURED;
extern texture_T* TEXTURE_DEFAULT_FONT;

/**
 * Update projection and view matrices in the current active shader.
 *
 * @param unsigned int shader_program
 * @param projection_view_T* projection_view
 */
void send_projection_view_state(
    unsigned int shader_program,
    projection_view_T* projection_view
)
{
    glUniformMatrix4fv(
        glGetUniformLocation(shader_program, "projection"),
        1,
        GL_FALSE,
        (float *) projection_view->projection
    );

    glUniformMatrix4fv(
        glGetUniformLocation(shader_program, "view"),
        1,
        GL_FALSE,
        (float *) projection_view->view
    );
}

/**
 * Update the model matrice in the current active shader.
 *
 * @param unsigned int shader_program
 * @param mat4 model
 */
void send_model_state(unsigned int shader_program, mat4 model)
{
    unsigned uniform_mat4_model = glGetUniformLocation(shader_program, "model");
    glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);
}

/**
 * Draw a 2D mesh (unpositioned, not translated)
 *
 * @param float width
 * @param float height
 * @param float r
 * @param float g
 * @param float b
 * @param unsigned int VBO
 * @param unsigned int EBO
 */
void draw_2D_mesh(
    float width,
    float height,
    float r,
    float g,
    float b,
    unsigned int VBO,
    unsigned int EBO
)
{
    float VERTICES_TEXTURED[] =
    {
        // positions            // colors                             // texture coords
        0.0f,   0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   0.0f, 0.0f,   // top right
        width,  0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   1.0f, 0.0f,   // bottom right
        width,  height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   1.0f, 1.0f,   // bottom left
        0.0f,   height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   0.0f, 1.0f    // top left
    };

    unsigned int INDICES_DEFAULT [] =
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES_TEXTURED), VERTICES_TEXTURED, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/**
 * Draw a positioned, translated 2D mesh.
 *
 * @param float x
 * @param float y
 * @param float z
 * @param float width
 * @param float height
 * @param float r
 * @param float g
 * @param float b
 * @param state_T* state
 */
void draw_positioned_2D_mesh(
    float x,
    float y,
    float z,
    float width,
    float height,
    float r,
    float g,
    float b,
    state_T* state
)
{
    glBindVertexArray(state->VAO);
    glUseProgram(SHADER_COLORED);

    send_projection_view_state(SHADER_COLORED, state->camera->projection_view); 

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

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
    send_model_state(SHADER_COLORED, model); 

    draw_2D_mesh(width, height, r, g, b, VBO, EBO);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glm_translate(model, (vec3){-x, -y, -z});
    
    glBindVertexArray(0);
}

/**
 * Draw a line
 *
 * @param float x
 * @param float y
 * @param float z
 * @param float endx
 * @param float endy
 * @param float endz
 * @param float r
 * @param float g
 * @param float b
 * @param state_T* state
 */
void draw_line(
    float x,
    float y,
    float z,
    float endx,
    float endy,
    float endz,
    float r,
    float g,
    float b,
    state_T* state
)
{
    glBindVertexArray(state->VAO);
    glUseProgram(SHADER_COLORED);

    send_projection_view_state(SHADER_COLORED, state->camera->projection_view); 

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    mat4 model =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    glm_translate(model, (vec3){0.0f, 0.0f, 0.0f});
    send_model_state(SHADER_COLORED, model);

    float VERTICES[] =
    {
        // positions               // colors                             
        x,       y,       z,       r / 255.0f, g / 255.0f, b / 255.0f,
        endx,    endy,    endz,    r / 255.0f, g / 255.0f, b / 255.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, 3);

    glDeleteBuffers(1, &VBO);

    glBindVertexArray(0);
}

/**
 * Used to draw a text at a specific position.
 *
 * @param const char* text
 * @param float x
 * @param float y
 * @param float z
 * @param float r
 * @param float g
 * @param float b
 * @param float size
 * @param float spacing
 */
void draw_text(
    const char* text,
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    float size,
    float spacing,
    state_T* state
)
{
    float d_r = r / 255.0f;
    float d_g = g / 255.0f;
    float d_b = b / 255.0f;

    float vertices[] = 
    {
        // positions          // colors           // texture coords
        size,  size, 0.0f,   d_r, d_g, d_b,   1.0f, 1.0f,   // top right
        size, -size, 0.0f,   d_r, d_g, d_b,   1.0f, 0.0f,   // bottom right
        -size, -size, 0.0f,   d_r, d_g, d_b,   0.0f, 0.0f,   // bottom left
        -size,  size, 0.0f,   d_r, d_g, d_b,   0.0f, 1.0f    // top left
    };

    unsigned int indices [] =
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
   
    glBindVertexArray(state->VAO);
    glUseProgram(SHADER_TEXTURED);
    send_projection_view_state(SHADER_TEXTURED, state->camera->projection_view);
    
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

        glActiveTexture(GL_TEXTURE0);
        unsigned int tex = get_char_texture_from_texture(c, 7, 7, 8, 12, TEXTURE_DEFAULT_FONT);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(glGetUniformLocation(SHADER_TEXTURED, "ourTexture"), 0); 
        glBindVertexArray(state->VAO);
        
        unsigned uniform_mat4_model = glGetUniformLocation(SHADER_TEXTURED, "model");
        glm_translate(model, (vec3){(i * (size + spacing)), 0, 0});
        glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDeleteBuffers(1, &EBO);
        glDeleteTextures(1, &tex);
    }

    glDeleteBuffers(1, &VBO);
    glBindVertexArray(0);
}
