#ifndef COELUM_SHADER_MANAGER_H
#define COELUM_SHADER_MANAGER_H
#include "dynamic_list.h"


typedef struct SHADER_MANAGER_STRUCT
{
    dynamic_list_T* programs;
} shader_manager_T;

shader_manager_T* init_shader_manager();

void shader_manager_free(shader_manager_T* shader_manager);

typedef struct SHADER_MANAGER_PROGRAM_STRUCT
{
    char* name;
    unsigned int program;
} shader_manager_program_T;

shader_manager_program_T* init_shader_manager_program(char* name, unsigned int program);

void shader_manager_program_free(shader_manager_program_T* shader_manager_program);

unsigned int shader_manager_register_program(
    shader_manager_T* sm,
    char* name,
    char* fragment_src_filename,
    char* vertex_src_filename
);

unsigned int shader_manager_get_program(shader_manager_T* sm, char* name);
#endif
