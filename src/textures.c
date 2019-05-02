#include "include/textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


texture_t* get_texture(char* filepath) {
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

    if (tex->data) { 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else {
        printf("Failed to load texture\n");
    }

    //stbi_image_free(data);

    tex->renderable_texture = texture;

    return tex;
}

unsigned int get_subtexture(texture_t* texture, int x, int y, int h, int w) {
    unsigned int cut_texture;
    glGenTextures(1, &cut_texture);
    glBindTexture(GL_TEXTURE_2D, cut_texture);
    /*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei( GL_UNPACK_ROW_LENGTH, texture->width );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, x );
    glPixelStorei( GL_UNPACK_SKIP_ROWS, y );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
    glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );


    return cut_texture;
}
