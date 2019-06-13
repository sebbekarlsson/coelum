#include "include/shader_registry.h"


unsigned int SHADER_TEXTURED;
unsigned int SHADER_TEXTURED_SHADED;
unsigned int SHADER_COLORED;

/**
 * All shader programs goes here.
 *
 * @param shader_manager_T* shader_manager
 */
void register_shader_programs(shader_manager_T* shader_manager)
{
    SHADER_TEXTURED = shader_manager_register_program(
        shader_manager,
        "textured",
        "fragment_textured.fs.glsl",
        "vertex.vs.glsl"
    );

    SHADER_TEXTURED_SHADED = shader_manager_register_program(
        shader_manager,
        "textured",
        "fragment_textured_shaded.fs.glsl",
        "vertex.vs.glsl"
    );

    SHADER_COLORED = shader_manager_register_program(
        shader_manager,
        "colored",
        "fragment_colored.fs.glsl",
        "vertex.vs.glsl"
    );
}
