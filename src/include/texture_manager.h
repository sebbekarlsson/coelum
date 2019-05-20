#ifndef COELUM_TEXTURE_MANAGER_H
#define COELUM_TEXTURE_MANAGER_H
#include "dynamic_list.h"
#include "textures.h"
#include <glad/glad.h> 


typedef struct TEXTURE_MANAGER_STRUCT {
    dynamic_list_T* textures;
} texture_manager_T;

typedef struct TEXTURE_MANAGER_TEXTURE_STRUCT {
    char* name;
    texture_T* texture;
} texture_manager_texture_T;

texture_manager_T* init_texture_manager();

texture_manager_texture_T* init_texture_manager_texture();

texture_T* texture_manager_register_texture(
    texture_manager_T* texture_manager,
    char* texture_src_filename,
    int mode
);

texture_T* texture_manager_get_texture(texture_manager_T* texture_manager, char* name);
#endif
