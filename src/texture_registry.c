#include "include/texture_registry.h"
#include <glad/glad.h> 


texture_T* TEXTURE_DEFAULT_FONT;
texture_T* TEXTURE_LN_EGA8x8_FONT;

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

    TEXTURE_LN_EGA8x8_FONT = texture_manager_register_texture(
        texture_manager,
        "/usr/local/share/coelum/res/font/LN_EGA8x8.png",
        GL_RGBA
    );
}
