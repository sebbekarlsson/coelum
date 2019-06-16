#include "include/sprite.h"
#include "include/draw_utils.h"
#include "include/textures.h"
#include <glad/glad.h> 


extern unsigned int SHADER_TEXTURED;

/**
 * Initialize a new sprite from a list of textures.
 *
 * @param dynamic_list_T* textures
 * @param float frame_deplay
 * @param float width
 * @param float height
 *
 * @return sprite_T*
 */
sprite_T* init_sprite(dynamic_list_T* textures, float frame_delay, float width, float height)
{
    sprite_T* sprite = calloc(1, sizeof(struct SPRITE_STRUCT));
    sprite->textures = textures;
    sprite->index = 0;
    sprite->width = width;
    sprite->height = height;
    sprite->r = 255;
    sprite->g = 255;
    sprite->b = 255;
    sprite->frame_delay = frame_delay;
    gettimeofday(&sprite->timer, 0);

    glGenBuffers(1, &sprite->VBO);
    glGenBuffers(1, &sprite->EBO);

    return sprite;
}

/**
 * Initialize a new sprite from a filename.
 *
 * @param const char* filename
 * @param int mode
 * @param float frame_delay
 * @param float width
 * @param float height
 *
 * @return sprite_T*
 */
sprite_T* init_sprite_from_file(const char* filename, int mode, float frame_delay, float width, float height)
{
    sprite_T* sprite = calloc(1, sizeof(struct SPRITE_STRUCT));
    sprite->textures = init_dynamic_list(sizeof(struct TEXTURE_STRUCT));
    dynamic_list_append(sprite->textures, get_texture(filename, mode));

    sprite->index = 0;
    sprite->width = width;
    sprite->height = height;
    sprite->r = 255;
    sprite->g = 255;
    sprite->b = 255;
    sprite->frame_delay = frame_delay;
    gettimeofday(&sprite->timer, 0);


    glGenBuffers(1, &sprite->VBO);
    glGenBuffers(1, &sprite->EBO);

    return sprite;
}

/**
 * Draw a sprite within a state.
 *
 * @param sprite_T* sprite
 * @param state_T* state
 */
void sprite_draw(sprite_T* sprite, state_T* state)
{
    glBindVertexArray(state->VAO);

    texture_T* texture = (texture_T*) sprite->textures->items[sprite->index];

    glUseProgram(SHADER_TEXTURED);

    glUniform1i(glGetUniformLocation(SHADER_TEXTURED, "ourTexture"), 0); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->renderable_texture);

    draw_2D_mesh(
        sprite->width,
        sprite->height,
        sprite->r, sprite->g, sprite->b,  // r, g, b
        sprite->VBO,
        sprite->EBO        
    );

    struct timeval end;
    gettimeofday(&end, 0);

    time_t curtime = end.tv_sec;

    float time_spent = (double)(end.tv_usec - sprite->timer.tv_usec) / 1000000 + (double)(end.tv_sec - sprite->timer.tv_sec);

    if (time_spent >= sprite->frame_delay)
    {
        if (sprite->index < sprite->textures->size - 1)
        {
            sprite->index += 1;
        }
        else
        {
            sprite->index = 0;
        }
        
        gettimeofday(&sprite->timer, 0);
    }

    glBindVertexArray(0);
}

/**
 * Deallocation method for sprite_T
 */
void sprite_free(sprite_T* sprite)
{
    for (int i = 0; i < sprite->textures->size; i++)
        free(sprite->textures->items[i]);

    free(sprite->textures);
    free(sprite);
}
