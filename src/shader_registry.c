#include "include/shader_registry.h"


unsigned int SHADER_TEXTURED;
unsigned int SHADER_COLORED;

/**
 * All shader programs goes here.
 *
 * @param shader_manager* sm
 */
void register_shader_programs(shader_manager* sm)
{
    SHADER_TEXTURED = shader_manager_register_program(
        sm,
        "textured",
        "fragment_textured.fs.glsl",
        "vertex.vs.glsl"
    );

    SHADER_COLORED = shader_manager_register_program(
        sm,
        "colored",
        "fragment_colored.fs.glsl",
        "vertex.vs.glsl"
    );
}
