#include "include/shader_registry.h"


/**
 * All shader programs goes here
 */
void register_shader_programs(shader_manager* sm) {
    shader_manager_register_program(sm, "default", "fragment.fs.glsl", "vertex.vs.glsl");
}
