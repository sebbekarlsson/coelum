#include "include/draw_utils.h"
#include "include/shader_registry.h"
#include "include/textures.h"
#include "include/font.h"
#include <string.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


extern unsigned int SHADER_COLORED;
extern unsigned int SHADER_TEXTURED;
extern unsigned int SHADER_TEXTURED_SHADED;
extern unsigned int SHADER_TEXTURED_TTF;

extern texture_T* TEXTURE_DEFAULT_FONT;
extern texture_T* TEXTURE_LN_EGA8x8_FONT;

unsigned int INDICES_DEFAULT [] =
{
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

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
 * @param float a
 * @param unsigned int VBO
 * @param unsigned int EBO
 */
void draw_2D_mesh(
    float width,
    float height,
    float r,
    float g,
    float b,
    float a,
    unsigned int VBO,
    unsigned int EBO
)
{
    float VERTICES_TEXTURED[] =
    {
        // positions            // colors                                // texture coords
        0.0f,   0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   0.0f, 0.0f,   // top right
        width,  0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   1.0f, 0.0f,   // bottom right
        width,  height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   1.0f, 1.0f,   // bottom left
        0.0f,   height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   0.0f, 1.0f    // top left
    }; 

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES_TEXTURED), VERTICES_TEXTURED, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES_DEFAULT), INDICES_DEFAULT, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // texcoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
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
 * @param float a
 * @param state_T* state
 *
 * TODO: add support for rotations
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
    float a,
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

    draw_2D_mesh(width, height, r, g, b, a, VBO, EBO);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glBindVertexArray(0);
}

/**
 * Draws the first frame of a sprite, positioned.
 *
 * @param sprite_T* sprite
 * @param float x
 * @param float y
 * @param float z
 * @param float width
 * @param float height
 * state_T* state
 */
void draw_positioned_sprite(
    sprite_T* sprite,
    float x,
    float y,
    float z,
    float width,
    float height,
    state_T* state
)
{
    glBindVertexArray(state->VAO);
    glUseProgram(SHADER_TEXTURED);

    send_projection_view_state(SHADER_TEXTURED, state->camera->projection_view); 

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
    send_model_state(SHADER_TEXTURED, model);

    glUniform1i(glGetUniformLocation(SHADER_TEXTURED, "ourTexture"), 0);

    sprite_draw(sprite, state);

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

    //glBindVertexArray(0);
}

void draw_3D_axis(float x, float y, float z, float width, float height, float depth, state_T* state)
{
    // x
    draw_line(
        x, y, z,
        x + width, y, z,
        255, 0, 0,
        state
    );

    // y
    draw_line(
        x, y, z,
        x, y + height, z,
        0, 255, 0,
        state
    );

    // z
    draw_line(
        x, y, z,
        x, y, z + depth,
        0, 0, 255,
        state
    );
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
 * @param float a
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
    float a,
    float size,
    float spacing,
    unsigned int limit,
    state_T* state
)
{
    float d_r = r / 255.0f;
    float d_g = g / 255.0f;
    float d_b = b / 255.0f;

    float vertices[] = 
    {
        // positions          // colors           // texture coords
        size,  size, 0.0f,   d_r, d_g, d_b, a,   1.0f, 1.0f,   // top right
        size, -size, 0.0f,   d_r, d_g, d_b, a,   1.0f, 0.0f,   // bottom right
        -size, -size, 0.0f,   d_r, d_g, d_b, a,   0.0f, 0.0f,   // bottom left
        -size,  size, 0.0f,   d_r, d_g, d_b, a,   0.0f, 1.0f    // top left
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

    int char_pos = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];

        if (c == '\r' || c == '\n' || c == 0 || c == '\0' || (int) c == 10)
            continue;

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texcoords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glActiveTexture(GL_TEXTURE0);
        //unsigned int tex = get_char_texture_from_texture(c, 7, 7, 8, 12, TEXTURE_DEFAULT_FONT);
        unsigned int tex = get_char_texture_from_texture(c, 8, 8, 16, 16, TEXTURE_LN_EGA8x8_FONT);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(glGetUniformLocation(SHADER_TEXTURED, "ourTexture"), 0); 
        glBindVertexArray(state->VAO);
        
        unsigned uniform_mat4_model = glGetUniformLocation(SHADER_TEXTURED, "model");
        glm_translate(model, (vec3){(char_pos * (size + spacing)), 0, z});
        glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *) 0);
        glDeleteBuffers(1, &EBO);
        glDeleteTextures(1, &tex);

        if (limit)
        {
            if (char_pos >= limit)
                break;
        }

        char_pos += 1;
    }

    glDeleteBuffers(1, &VBO);
    glBindVertexArray(0); 
}

/**
 * Used to draw a text at a specific position with ttf font.
 *
 * @param const char* text
 * @param const char* fontpath
 * @param float x
 * @param float y
 * @param float z
 * @param float r
 * @param float g
 * @param float b
 * @param float a
 * @param float size
 * @param float spacing
 */
void draw_text_ttf(
    const char* text,
    const char* fontpath,
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    float a,
    float size,
    float spacing,
    unsigned int limit,
    state_T* state
)
{
    dynamic_list_T* character_list = get_char_glyphs_from_text(
        text,
        fontpath,
        size 
    );

    float scale = 1.0f;

    float d_r = r / 255.0f;
    float d_g = g / 255.0f;
    float d_b = b / 255.0f; 

    unsigned int indices [] =
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
   
    glBindVertexArray(state->VAO);
    glUseProgram(SHADER_TEXTURED_TTF);
    send_projection_view_state(SHADER_TEXTURED_TTF, state->camera->projection_view);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    int char_pos = 0;

    /**
     * Draw every character
     */
    float xx = x;
    float yy = y;
    for (int i = 0; i < character_list->size; i++)
    {
        font_character_T* character = (font_character_T*) character_list->items[i];

        if (character->value == '\n')
        {
            yy -= size;
            xx = 0;
            continue;
        }

        unsigned int texture = character->texture;

        GLfloat xpos = xx + character->bearing_left * scale;
        GLfloat ypos = yy + (character->height - character->bearing_top) * scale;

        GLfloat w = character->width * scale;
        GLfloat h = character->height * scale;

        float vertices[] = 
        {
            // positions          // colors           // texture coords
            0,      0,   0.0f,   d_r, d_g, d_b, a,       0.0f, 0.0f,   // top right
            0 + w,  0,   0.0f,   d_r, d_g, d_b, a,       1.0f, 0.0f,   // bottom right
            0 + w,  0 - h,   0.0f,   d_r, d_g, d_b, a,   1.0f, -1.0f,   // bottom left
            0,      0 - h,   0.0f,   d_r, d_g, d_b, a,   0.0f, -1.0f    // top left
        };

        unsigned int EBO;

        glGenBuffers(1, &EBO);

        mat4 model =
        {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        
        glm_translate(model, (vec3){xpos, ypos, z});

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texcoords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(SHADER_TEXTURED_TTF, "ourTexture"), 0); 
        glBindVertexArray(state->VAO);
        
        unsigned uniform_mat4_model = glGetUniformLocation(SHADER_TEXTURED, "model");

        glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid *) 0);
        glDeleteBuffers(1, &EBO); 

        if (limit)
        {
            if (char_pos >= limit)
                break;
        }

        xx += (character->advance >> 6) * scale;
    }

    glDeleteBuffers(1, &VBO);
    glBindVertexArray(0);

    free_font_character_list(character_list);
}

/**
 * Draw a 3D model at a position.
 *
 * @param obj_T* obj
 * @param unsigned int texture
 * @param float x
 * @param float y
 * @param float z
 * @param float r
 * @param float g
 * @param float b
 * @param state_T* state
 */
void draw_3D_model(
    obj_T* obj,
    unsigned int texture,
    float x,
    float y,
    float z,
    float r,
    float g,
    float b,
    state_T* state
)
{
    float d_r = r / 255.0f;
    float d_g = g / 255.0f;
    float d_b = b / 255.0f;

    glBindVertexArray(state->VAO);
    glUseProgram(SHADER_TEXTURED_SHADED);
    send_projection_view_state(SHADER_TEXTURED_SHADED, state->camera->projection_view);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float* vecs = calloc(1, sizeof(float));
    vecs[0] = 0;
    size_t vec_size = 0;
    
    for (int j = 0; j < obj->polygon_groups_size; j++)
    {
        for (int k = 0; k < obj->polygon_groups[j]->faces_size; k++)
        {
            obj_face_T* face = obj->polygon_groups[j]->faces[k];

            for (int l = 0; l < face->vertex_pointers_size; l++)
            {
                obj_vec_T* facevec = obj->vertice_vectors[face->vertex_pointers[l] - 1];
                obj_vec_T* texvec = (void*) 0;
                obj_vec_T* normalvec = (void*) 0;

                if (obj->texcoord_vectors_size && face->texcoord_pointers_size)
                    texvec = obj->texcoord_vectors[face->texcoord_pointers[l] - 1];

                if (obj->normal_vectors_size && face->normal_pointers_size)
                    normalvec = obj->normal_vectors[face->normal_pointers[l] - 1];

                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = facevec->x;

                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = facevec->y;

                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = facevec->z; 

                // colors
                
                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = d_r;

                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = d_g;

                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = d_b;

                if (texvec)
                {
                    vec_size++;
                    vecs = realloc(vecs, vec_size * sizeof(float));
                    vecs[vec_size - 1] = texvec->x;

                    vec_size++;
                    vecs = realloc(vecs, vec_size * sizeof(float));
                    vecs[vec_size - 1] = -texvec->y;
                }
                else
                {
                    vec_size++;
                    vecs = realloc(vecs, vec_size * sizeof(float));
                    vecs[vec_size - 1] = 0.0f;

                    vec_size++;
                    vecs = realloc(vecs, vec_size * sizeof(float));
                    vecs[vec_size - 1] = 0.0f;
                }

                // normals
                
                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = normalvec->x;

                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = normalvec->y;

                vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = normalvec->z;
                
                /*vec_size++;
                vecs = realloc(vecs, vec_size * sizeof(float));
                vecs[vec_size - 1] = texvec->z;*/
            }
        }
    }

    mat4 model =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    glm_translate(model, (vec3){x, y, z});

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vec_size * sizeof(float), &vecs[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(SHADER_TEXTURED_SHADED, "ourTexture"), 0);
    
    glBindVertexArray(state->VAO);
    
    unsigned uniform_mat4_model = glGetUniformLocation(SHADER_TEXTURED_SHADED, "model");
    glUniformMatrix4fv(uniform_mat4_model, 1, GL_FALSE, (float *) model);

    glUniform3fv(glGetUniformLocation(SHADER_TEXTURED_SHADED, "world_pos"), 1, (float[]){ x, y, z });

    glDrawArrays(GL_TRIANGLES, 0, vec_size);

    glDeleteBuffers(1, &VBO);
    glBindVertexArray(0);
}
