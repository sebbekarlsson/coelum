#include "include/texture_registry.h"


texture_t* TEXTURE_DEFAULT_FONT;

/**
 * All textures goes here.
 *
 * @param texture_manager* _tm
 */
void register_textures(texture_manager* _tm)
{
    TEXTURE_DEFAULT_FONT = texture_manager_register_texture(
        _tm,
        "/usr/local/share/coelum/res/font/null_terminator.png",
        GL_RGBA
    );
}
