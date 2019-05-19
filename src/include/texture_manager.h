#ifndef COELUM_TEXTURE_MANAGER_H
#define COELUM_TEXTURE_MANAGER_H
#include "dynamic_list.h"
#include "textures.h"
#include <glad/glad.h> 


typedef struct TEXTURE_MANAGER_STRUCT {
    dynamic_list* textures;
} texture_manager;

typedef struct TEXTURE_MANAGER_TEXTURE_STRUCT {
    char* name;
    texture_t* texture;
} texture_manager_texture;

texture_manager* init_texture_manager();

texture_manager_texture* init_texture_manager_texture();

texture_t* texture_manager_register_texture(
    texture_manager* _tm,
    char* texture_src_filename,
    int mode
);

texture_t* texture_manager_get_texture(texture_manager* sm, char* name);
#endif
