#ifndef PONG_TEXTURES_H
#define PONG_TEXTURES_H

typedef struct TEXTURE_STRUCT {
    unsigned char* data;
    unsigned int renderable_texture;
    int width;
    int height;
} texture_t;

texture_t* get_texture(char* filepath);

unsigned int get_subtexture(texture_t* texture, int x, int y, int h, int w);
#endif
