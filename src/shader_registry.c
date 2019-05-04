#include "include/shader_registry.h"


unsigned int SHADER_DEFAULT;

/**
 * All shader programs goes here.
 *
 * @param shader_manager* sm
 */
void register_shader_programs(shader_manager* sm)
{
    SHADER_DEFAULT = shader_manager_register_program(
        sm,
        "default",
        "fragment.fs.glsl",
        "vertex.vs.glsl"
    );
}
