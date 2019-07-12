#ifndef COELUM_TEXTURES_H
#define COELUM_TEXTURES_H


typedef struct TEXTURE_STRUCT
{
    unsigned char* data;
    unsigned int renderable_texture;
    int width;
    int height;
} texture_T;

texture_T* get_texture(const char* filepath, int mode);

texture_T* get_texture_from_data(unsigned char* data, int width, int height, int mode);

unsigned int get_subtexture_raw(texture_T* texture, int x, int y, int w, int h);

texture_T* get_subtexture(texture_T* texture, int x, int y, int w, int h);

unsigned int get_char_texture_from_texture(
    char c,
    int char_w,
    int char_h,
    int n_rows_x,
    int n_rows_y,
    texture_T* font_texture
);

void texture_free(texture_T* texture);
#endif
