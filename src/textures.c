#include "include/textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


/**
 * Creates a new instance of texture_t and loads a texture to it.
 *
 * @param char* filepath - path to file
 *
 * @return texture_t*
 */
texture_t* get_texture(char* filepath)
{
    texture_t* tex = calloc(1, sizeof(struct TEXTURE_STRUCT));

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int nrChannels;
    tex->data = stbi_load(filepath, &tex->width, &tex->height, &nrChannels, 0);

    if (tex->data)
    { 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture\n");
    }

    //stbi_image_free(data);

    tex->renderable_texture = texture;

    return tex;
}

/**
 * "Cut" out a piece of a texture
 *
 * @param texture_t* texture
 * @param int x
 * @param int y
 * @param int h
 * @param int w
 *
 * @return unsigned int
 */
unsigned int get_subtexture(texture_t* texture, int x, int y, int h, int w)
{
    unsigned int cut_texture;
    glGenTextures(1, &cut_texture);
    glBindTexture(GL_TEXTURE_2D, cut_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, texture->width);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, x);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, y);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);


    return cut_texture;
}

/**
 * Use this to get character from texture.
 * This function uses the `get_subtexture` method.
 *
 * @param char c
 * @param int char_w
 * @param int char_h
 * @param int n_rows_x
 * @param int n_rows_y
 * @param texture_t* font_texture
 */
unsigned int get_char_texture_from_texture(
    char c,
    int char_w,
    int char_h,
    int n_rows_x,
    int n_rows_y,
    texture_t* font_texture
)
{
    int x = 0;
    int y = 0;

    /*
     * The `a` character begins at position `33` in
     * `res/font/null_terminator.png`
     */
    int ptr = -97 + (int) c + 33;

    for (int i = 0; i < n_rows_x * n_rows_y; i++)
    {
        if (i <= ptr)
        {
            if (i % n_rows_x == 0 && i != 0)
            {
                // we reached the end of the row, lets move down, and also
                // back to the left.
                
                y += 1;
                x = 0;
            }
            else
            {
                // we are still just moving right.
                
                x += 1;
            }
        }
        else
        {
            break;
        }
    }

    unsigned int texture = get_subtexture(
        font_texture,
        (char_w + 1) * x,
        (char_h + 1) * y,
        char_w,
        char_h
    );

    return texture;
}

/**
 * Deallocate a texture_t* instance.
 *
 * @param texture_t* texture
 */
void texture_free(texture_t* texture)
{
    stbi_image_free(texture->data);
    free(texture);
}
