#include "include/font.h"


extern texture_T* TEXTURE_LN_EGA8x8_FONT;

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
        }
    }
}
