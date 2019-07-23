#ifndef COELUM_FILE_UTILS_H
#define COELUM_FILE_UTILS_H
#include "sprite.h"
#include <glad/glad.h>


void write_sprite_to_disk(sprite_T* sprite, const char* filename);

sprite_T* load_sprite_from_disk(const char* filename);
#endif
