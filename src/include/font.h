#ifndef COELUM_FONT_H
#define COELUM_FONT_H
#include "textures.h"
#include "dynamic_list.h"
#include <cglm/cglm.h>
#include <cglm/call.h>
#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct FONT_CHARACTER_STRUCT
{
    unsigned int texture;   // ID handle of the glyph texture
    float width;
    float height;
    float bearing_left;
    float bearing_top;
    unsigned int advance;    // Horizontal offset to advance to next glyph
    char value;
} font_character_T;

font_character_T* init_font_character(FT_Face face, char c);

void free_font_character(font_character_T* font_character);

void free_font_character_list(dynamic_list_T* font_character_list);

FT_Face get_face_from_character(char c, const char* fontpath, unsigned int size);

font_character_T* get_char_glyph(char c, const char* fontpath, unsigned int size);

dynamic_list_T* get_char_glyphs_from_text(const char* text, const char* fontpath, unsigned int size);

void get_font_coords(char c, texture_T* font, int* x, int *y);
#endif
