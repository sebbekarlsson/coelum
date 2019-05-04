#ifndef PONG_SHADER_MANAGER_H
#define PONG_SHADER_MANAGER_H
#include "dynamic_list.h"
#include <glad/glad.h> 


typedef struct SHADER_MANAGER_STRUCT {
    dynamic_list* programs;
    dynamic_list* program_names;
} shader_manager;

typedef struct SHADER_MANAGER_PROGRAM_STRUCT {
    char* name;
    unsigned int program;
} shader_manager_program;

shader_manager* init_shader_manager();

shader_manager_program* init_shader_manager_program();

unsigned int shader_manager_register_program(
    shader_manager* sm,
    char* name,
    char* fragment_src_filename,
    char* vertex_src_filename
);

unsigned int shader_manager_get_program(shader_manager* sm, char* name);
#endif
