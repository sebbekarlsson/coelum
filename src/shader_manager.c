#include "include/shader_manager.h"
#include "include/io.h"
#include <string.h>
#include <glad/glad.h> 


/**
 * Creates a new shader_manager
 * 
 * @return shader_manager_T*
 */
shader_manager_T* init_shader_manager()
{
    shader_manager_T* shader_manager = calloc(1, sizeof(struct SHADER_MANAGER_STRUCT));
    shader_manager->programs = init_dynamic_list(sizeof(struct SHADER_MANAGER_PROGRAM_STRUCT));

    return shader_manager;
}

void shader_manager_free(shader_manager_T* shader_manager)
{
    for (int i = 0; i < shader_manager->programs->size; i++)
    {
        //printf("Freeing shader number %d\n", i);
        //shader_manager_program_T* shader_manager_program = (shader_manager_program_T*) shader_manager->programs->items[i];
        //shader_manager_program_free(shader_manager_program);
    }

    free(shader_manager->programs);
    free(shader_manager);
}

/**
 * Creates a new shader_manager_program
 *
 * @param char* name - the name of the programe
 * @param unsigned int program - the program
 *
 * @return shader_manager_program_T*
 */
shader_manager_program_T* init_shader_manager_program(char* name, unsigned int program)
{
    shader_manager_program_T* shader_managerp = calloc(1, sizeof(struct SHADER_MANAGER_PROGRAM_STRUCT));
    shader_managerp->name = name;
    shader_managerp->program = program;

    return shader_managerp;
}

void shader_manager_program_free(shader_manager_program_T* shader_manager_program)
{
    printf("Deallocating shader_manager_program...\n");

    glDeleteProgram(shader_manager_program->program);
    free(shader_manager_program);
}

/**
 * Registers a shader program to a shader_manager.
 * This method also compiles a shader based on fragment and vertex shader
 * sources.
 *
 * shader_manager_T* shader_manager
 * char* name
 * char* fragment_src_filename
 * char* vertex_src_filename
 */
unsigned int shader_manager_register_program(
    shader_manager_T* shader_manager,
    char* name,
    char* fragment_src_filename,
    char* vertex_src_filename
) {
    char* f = calloc(256, sizeof(char));
    sprintf(f, "/usr/local/share/coelum/res/shaders/%s", fragment_src_filename);
    char* fragment_src = read_file(f);
    const char* fragment_src_ptr = (const char*) fragment_src;
    free(f);

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_src_ptr, NULL);
    glCompileShader(fragment_shader);
    free(fragment_src);

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
    sprintf(v, "/usr/local/share/coelum/res/shaders/%s", vertex_src_filename);
    char* vertex_src = read_file(v);
    const char* vertex_src_ptr = (const char*) vertex_src;
    free(v);

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_src_ptr, NULL);
    glCompileShader(vertex_shader);
    free(vertex_src);

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

    shader_manager_program_T* shader_managerp = init_shader_manager_program(name, shader_program);
    dynamic_list_append(shader_manager->programs, shader_managerp);
    
    return shader_program;
}

/**
 * Use this to get a registered shader program
 *
 * @param shader_manager_T* shader_manager
 * @param char* name
 *
 * @return unsigned int
 */
unsigned int shader_manager_get_program(shader_manager_T* shader_manager, char* name)
{
    for (int i = 0; i < shader_manager->programs->size; i++)
    {
        shader_manager_program_T* shader_managerp = (shader_manager_program_T*) shader_manager->programs->items[i];

        if (strcmp(shader_managerp->name, name) == 0)
            return shader_managerp->program;
    }

    return -1;
}
