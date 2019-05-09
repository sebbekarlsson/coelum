#include "include/texture_manager.h"
#include "include/io.h"
#include <string.h>


/**
 * Creates a new texture_manager
 * 
 * @return texture_manager*
 */
texture_manager* init_texture_manager()
{
    texture_manager* sm = calloc(1, sizeof(struct TEXTURE_MANAGER_STRUCT));
    sm->textures = init_dynamic_list(sizeof(struct TEXTURE_MANAGER_TEXTURE_STRUCT));

    return sm;
}

/**
 * Creates a new texture_manager_texture
 *
 * @param char* name - the name of the texturee
 * @param texture_t* texture - the texture
 *
 * @return texture_manager_texture*
 */
texture_manager_texture* init_texture_manager_texture(char* name, texture_t* texture)
{
    texture_manager_texture* smp = calloc(1, sizeof(struct TEXTURE_MANAGER_TEXTURE_STRUCT));
    smp->name = name;
    smp->texture = texture;

    return smp;
}

/**
 * Registers a shader texture to a texture_manager.
 *
 * @param texture_manager* _tm
 * @param char* name
 * @param char* texture_src_filename
 *
 * @return texture_t*
 */
texture_t* texture_manager_register_texture(
    texture_manager* _tm,
    char* texture_src_filename,
    int mode
) {
    texture_t* texture = get_texture(texture_src_filename, mode);
    texture_manager_texture* tm_texture = init_texture_manager_texture(texture_src_filename, texture);

    dynamic_list_append(_tm->textures, tm_texture);

    return texture;
}

/**
 * Use this to get a registered texture
 *
 * @param texture_manager* _tm
 * @param char* name
 *
 * @return texture_t*
 */
texture_t* texture_manager_get_texture(texture_manager* _tm, char* name)
{
    for (int i = 0; i < _tm->textures->size; i++)
    {
        texture_manager_texture* tm_texture = (texture_manager_texture*) _tm->textures->items[i];

        if (strcmp(tm_texture->name, name) == 0)
            return tm_texture->texture;
    }

    return (void*) 0;
}
