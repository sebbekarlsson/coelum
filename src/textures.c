#include "include/textures.h"
#include "include/font.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <ctype.h>


extern texture_T* TEXTURE_LN_EGA8x8_FONT;


/**
 * Creates a new instance of texture_T and loads a texture to it.
 *
 * @param char* filepath - path to file
 *
 * @return texture_T*
 */
texture_T* get_texture(const char* filepath, int mode)
{
    texture_T* tex = calloc(1, sizeof(struct TEXTURE_STRUCT));

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
        glTexImage2D(GL_TEXTURE_2D, 0, mode, tex->width, tex->height, 0, mode, GL_UNSIGNED_BYTE, tex->data);
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
 * @param texture_T* texture
 * @param int x
 * @param int y
 * @param int w
 * @param int h
 *
 * @return unsigned int
 */
unsigned int get_subtexture_raw(texture_T* texture, int x, int y, int w, int h)
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
 * "Cut" out a piece of a texture
 *
 * @param texture_T* texture
 * @param int x
 * @param int y
 * @param int w
 * @param int h
 *
 * @return texture_T*
 */
texture_T* get_subtexture(texture_T* texture, int x, int y, int w, int h)
{
    texture_T* sub = calloc(1, sizeof(struct TEXTURE_STRUCT));
    sub->width = w;
    sub->height = h;
    sub->renderable_texture = get_subtexture_raw(texture, x, y, w, h);

    return sub;
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
 * @param texture_T* font_texture
 */
unsigned int get_char_texture_from_texture(
    char c,
    int char_w,
    int char_h,
    int n_rows_x,
    int n_rows_y,
    texture_T* font_texture
)
{
    int x, y = 0;

    get_font_coords(c, TEXTURE_LN_EGA8x8_FONT, &x, &y);

    unsigned int texture = get_subtexture_raw(
        font_texture,
        (char_w + 1) * x,
        (char_h + 1) * y,
        char_w,
        char_h
    );

    return texture;
}

/**
 * Deallocate a texture_T* instance.
 *
 * @param texture_T* texture
 */
void texture_free(texture_T* texture)
{
    stbi_image_free(texture->data);
    free(texture);
}
