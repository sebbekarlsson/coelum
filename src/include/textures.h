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

unsigned int get_char_texture_from_texture(
    char c,
    int char_w,
    int char_h,
    int n_rows_x,
    int n_rows_y,
    texture_t* font_texture
);
#endif
