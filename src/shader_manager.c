#include "include/shader_manager.h"
#include "include/io.h"
#include <string.h>


/**
 * Creates a new shader_manager
 * 
 * @return shader_manager*
 */
shader_manager* init_shader_manager()
{
    shader_manager* sm = calloc(1, sizeof(struct SHADER_MANAGER_STRUCT));
    sm->programs = init_dynamic_list(sizeof(struct SHADER_MANAGER_PROGRAM_STRUCT));

    return sm;
}

/**
 * Creates a new shader_manager_program
 *
 * @param char* name - the name of the programe
 * @param unsigned int program - the program
 *
 * @return shader_manager_program*
 */
shader_manager_program* init_shader_manager_program(char* name, unsigned int program)
{
    shader_manager_program* smp = calloc(1, sizeof(struct SHADER_MANAGER_PROGRAM_STRUCT));
    smp->name = name;
    smp->program = program;

    return smp;
}

/**
 * Registers a shader program to a shader_manager.
 * This method also compiles a shader based on fragment and vertex shader
 * sources.
 *
 * shader_manager* sm
 * char* name
 * char* fragment_src_filename
 * char* vertex_src_filename
 */
unsigned int shader_manager_register_program(
    shader_manager* sm,
    char* name,
    char* fragment_src_filename,
    char* vertex_src_filename
) {
    char* f = calloc(256, sizeof(char));
    sprintf(f, "res/shaders/%s", fragment_src_filename);
    const char* fragment_src = read_file(f);
    free(f);

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_src, NULL);
    glCompileShader(fragment_shader);

    int  success;
    char info_log[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("fragment_shader: %s\n", info_log);
        return -1;
    }

    char* v = calloc(256, sizeof(char));
    sprintf(v, "res/shaders/%s", vertex_src_filename);
    const char* vertex_src = read_file(v);
    free(v);

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_src, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("vertex_shader: %s\n", info_log);
        return -1;
    }

    unsigned int shader_program;
    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("shader_program: %s\n", info_log);
        return -1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    shader_manager_program* smp = init_shader_manager_program(name, shader_program);
    dynamic_list_append(sm->programs, smp);
    
    return shader_program;
}

/**
 * Use this to get a registered shader program
 *
 * @param shader_manager* sm
 * @param char* name
 *
 * @return unsigned int
 */
unsigned int shader_manager_get_program(shader_manager* sm, char* name)
{
    for (int i = 0; i < sm->programs->size; i++)
    {
        shader_manager_program* smp = (shader_manager_program*) sm->programs->items[i];

        if (strcmp(smp->name, name) == 0)
            return smp->program;
    }

    return -1;
}
