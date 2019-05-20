#include "include/texture_registry.h"


texture_T* TEXTURE_DEFAULT_FONT;

/**
 * All textures goes here.
 *
 * @param texture_manager_T* texture_manager
 */
void register_textures(texture_manager_T* texture_manager)
{
    TEXTURE_DEFAULT_FONT = texture_manager_register_texture(
        texture_manager,
        "/usr/local/share/coelum/res/font/null_terminator.png",
        GL_RGBA
    );
}
