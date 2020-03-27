#include "include/font.h"
#include "include/theatre.h"
#include <GL/glew.h>


extern texture_T* TEXTURE_LN_EGA8x8_FONT;
extern theatre_T* THEATRE;

font_character_T* init_font_character(FT_Face face, char c)
{
    font_character_T* character = calloc(1, sizeof(struct FONT_CHARACTER_STRUCT));

    // Generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    //glTexImage2D(GL_TEXTURE_2D, 0, mode, tex->width, tex->height, 0, mode, GL_UNSIGNED_BYTE, tex->data);
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    character->texture = texture;
    character->width = face->glyph->bitmap.width;
    character->height = face->glyph->bitmap.rows;
    character->bearing_left = face->glyph->bitmap_left;
    character->bearing_top = face->glyph->bitmap_top;
    character->advance = face->glyph->advance.x;
    character->value = c;

    glBindTexture(GL_TEXTURE_2D, 0); 

    return character;
}

void free_font_character(font_character_T* font_character)
{
    glDeleteTextures(1, &font_character->texture);
    free(font_character);
}

static void _free_font_character(void* item)
{
    free_font_character((font_character_T*) item);
}

void free_font_character_list(dynamic_list_T* font_character_list)
{
    dynamic_list_free(font_character_list, _free_font_character);
}

FT_Face get_face_from_character(char c, const char* fontpath, unsigned int size)
{
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&THEATRE->ft))
        perror("ERROR::FREETYPE: Could not init FreeType Library");

    // Load font as face
    FT_Face face;
    if (FT_New_Face(THEATRE->ft, fontpath, 0, &face))
        perror("ERROR::FREETYPE: Failed to load font");

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, size);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

    // Load character glyph 
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        perror("ERROR::FREETYTPE: Failed to load Glyph");
    
    return face;
}

font_character_T* get_char_glyph(char c, const char* fontpath, unsigned int size)
{
    FT_Face face = get_face_from_character(c, fontpath, size);
    font_character_T* character = init_font_character(face, c);

    FT_Done_Face(face);
    
    return character;
}

dynamic_list_T* get_char_glyphs_from_text(const char* text, const char* fontpath, unsigned int size)
{
    dynamic_list_T* list = init_dynamic_list(sizeof(struct FONT_CHARACTER_STRUCT*));
    for (int i = 0; i < strlen(text); i++)
    {
        font_character_T* character = get_char_glyph(text[i], fontpath, size);
        dynamic_list_append(list, character);
    }

    return list;
}

void get_font_coords(char c, texture_T* font, int* x, int* y)
{
    if (font == TEXTURE_LN_EGA8x8_FONT)
    {
        switch (c)
        {
            case 'a': *x = 1; *y = 6; break;
            case 'b': *x = 2; *y = 6; break;
            case 'c': *x = 3; *y = 6; break;
            case 'd': *x = 4; *y = 6; break;
            case 'e': *x = 5; *y = 6; break;
            case 'f': *x = 6; *y = 6; break;
            case 'g': *x = 7; *y = 6; break;
            case 'h': *x = 8; *y = 6; break;
            case 'i': *x = 9; *y = 6; break;
            case 'j': *x = 10; *y = 6; break;
            case 'k': *x = 11; *y = 6; break;
            case 'l': *x = 12; *y = 6; break;
            case 'm': *x = 13; *y = 6; break;
            case 'n': *x = 14; *y = 6; break;
            case 'o': *x = 15; *y = 6; break;
            case 'p': *x = 0; *y = 7; break;
            case 'q': *x = 1; *y = 7; break;
            case 'r': *x = 2; *y = 7; break;
            case 's': *x = 3; *y = 7; break;
            case 't': *x = 4; *y = 7; break;
            case 'u': *x = 5; *y = 7; break;
            case 'v': *x = 6; *y = 7; break;
            case 'w': *x = 7; *y = 7; break;
            case 'x': *x = 8; *y = 7; break;
            case 'y': *x = 9; *y = 7; break;
            case 'z': *x = 10; *y = 7; break;

            case 'A': *x = 1; *y = 4; break;
            case 'B': *x = 2; *y = 4; break;
            case 'C': *x = 3; *y = 4; break;
            case 'D': *x = 4; *y = 4; break;
            case 'E': *x = 5; *y = 4; break;
            case 'F': *x = 6; *y = 4; break;
            case 'G': *x = 7; *y = 4; break;
            case 'H': *x = 8; *y = 4; break;
            case 'I': *x = 9; *y = 4; break;
            case 'J': *x = 10; *y = 4; break;
            case 'K': *x = 11; *y = 4; break;
            case 'L': *x = 12; *y = 4; break;
            case 'M': *x = 13; *y = 4; break;
            case 'N': *x = 14; *y = 4; break;
            case 'O': *x = 15; *y = 4; break;
            case 'P': *x = 0; *y = 5; break;
            case 'Q': *x = 1; *y = 5; break;
            case 'R': *x = 2; *y = 5; break;
            case 'S': *x = 3; *y = 5; break;
            case 'T': *x = 4; *y = 5; break;
            case 'U': *x = 5; *y = 5; break;
            case 'V': *x = 6; *y = 5; break;
            case 'W': *x = 7; *y = 5; break;
            case 'X': *x = 8; *y = 5; break;
            case 'Y': *x = 9; *y = 5; break;
            case 'Z': *x = 10; *y = 5; break;

            case '0': *x = 0; *y = 3; break;
            case '1': *x = 1; *y = 3; break;
            case '2': *x = 2; *y = 3; break;
            case '3': *x = 3; *y = 3; break;
            case '4': *x = 4; *y = 3; break;
            case '5': *x = 5; *y = 3; break;
            case '6': *x = 6; *y = 3; break;
            case '7': *x = 7; *y = 3; break;
            case '8': *x = 8; *y = 3; break;
            case '9': *x = 9; *y = 3; break;

            case ' ': *x = 0; *y = 0; break;
            case '/': *x = 15; *y = 2; break;
            case '.': *x = 14; *y = 2; break;
            case ':': *x = 10; *y = 3; break;
            case ';': *x = 11; *y = 3; break;
            case '{': *x = 11; *y = 7; break;
            case '}': *x = 13; *y = 7; break;
            case '(': *x = 8; *y = 2; break;
            case ')': *x = 9; *y = 2; break;
            case '"': *x = 2; *y = 2; break;
            case '`': *x = 0; *y = 6; break;
            case '\\': *x = 12; *y = 5; break;
            case '=': *x = 13; *y = 3; break;
            case '!': *x = 1; *y = 2; break;
            case '<': *x = 12; *y = 3; break;
            case '>': *x = 14; *y = 3; break;
            case '+': *x = 11; *y = 2; break;
            case '-': *x = 13; *y = 2; break;
            case '_': *x = 15; *y = 5; break;
            case '?': *x = 15; *y = 3; break;
            case '$': *x = 4; *y = 2; break; 
            case ',': *x = 12; *y = 2; break;
            case '[': *x = 11; *y = 5; break;
            case ']': *x = 13; *y = 5; break;
            case '@': *x = 0; *y = 4; break;
        }
    }
}
