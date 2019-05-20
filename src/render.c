#include "include/render.h"
#include "include/shader_registry.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


extern unsigned int SHADER_COLORED;

void send_projection_view_state(unsigned int shader_program, projection_view_T* projection_view)
{
    if (!projection_view->uniform_mat4_view)
        projection_view->uniform_mat4_view = glGetUniformLocation(shader_program, "view");

    if (!projection_view->uniform_mat4_projection)
        projection_view->uniform_mat4_projection = glGetUniformLocation(shader_program, "projection");

    glUniformMatrix4fv(projection_view->uniform_mat4_projection, 1, GL_FALSE, (float *) projection_view->projection);
    glUniformMatrix4fv(projection_view->uniform_mat4_view, 1, GL_FALSE, (float *) projection_view->view);
}

void render_2D_mesh(
    float width,
    float height,
    float r,
    float g,
    float b,
    unsigned int VBO,
    unsigned int EBO
)
{
    float VERTICES_DEFAULT[] =
    {
        width,   height,   0.0f,  // top right
        width,   -height,   0.0f,  // bottom right
        -width,  -height,  0.0f,  // bottom left
        -width,  height,  0.0f   // top left 
    };

    float VERTICES_TEXTURED[] =
    {
        // positions                // colors  // texture coords
        0.0f,     0.0f,      0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   0.0f, 0.0f,   // top right
        width, 0.0f,      0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   1.0f, 0.0f,   // bottom right
        width, height, 0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   1.0f, 1.0f,   // bottom left
        0.0f,     height, 0.0f,  r / 255.0f, g / 255.0f, b / 255.0f,   0.0f, 1.0f    // top left
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

void render_2D_positioned_2D_mesh(
    float x,
    float y,
    float width,
    float height,
    float r,
    float g,
    float b,
    unsigned int VAO,
    projection_view_T* projection_view
)
{
    glBindVertexArray(VAO);
    glUseProgram(SHADER_COLORED);

    send_projection_view_state(SHADER_COLORED, projection_view); 

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

    glm_translate(model, (vec3){x, y, 0.0f});
    unsigned uniform_mat4_model = glGetUniformLocation(SHADER_COLORED, "model");
    glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);

    render_2D_mesh(width, height, r, g, b, VBO, EBO);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
