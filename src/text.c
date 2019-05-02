#include "include/text.h"
#include "include/textures.h"
#include <string.h>


#define CHAR_WIDTH 7
#define CHAR_HEIGHT 7


void render_text(const char* text) {
    texture_t* font_texture = get_texture("res/font/samplefont.gif");

    for (int i = 0; i < strlen(text); i++) {
        char c = text[i];

        unsigned int texture = get_subtexture(
            font_texture,
            1,
            0,
            CHAR_WIDTH,
            CHAR_HEIGHT
        );
    }
}

unsigned int get_char_a() {
    texture_t* font_texture = get_texture("res/font/null_terminator.png");

    unsigned int texture = get_subtexture(
        font_texture,
        2 + (7 * 3),
        4 + (7 * 4),
        CHAR_WIDTH,
        CHAR_HEIGHT
    );

    return texture;
}
