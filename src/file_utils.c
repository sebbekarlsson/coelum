#include "include/file_utils.h"
#include <coelum/textures.h>
#include <spr/spr.h>


void write_sprite_to_disk(sprite_T* sprite, const char* filename)
{
    spr_frame_T** frames = (void*) 0;
    size_t frames_size = 0;

    for (int i = 0; i < sprite->textures->size; i++)
    {
        texture_T* texture = (texture_T*) sprite->textures->items[i];
        spr_frame_T* frame = spr_init_frame_from_data(texture->data, texture->width, texture->height);
        frames_size += 1;
        frames = realloc(frames, frames_size * sizeof(struct SPR_FRAME_STRUCT*));
        frames[frames_size-1] = frame;
    }

    spr_T* spr = init_spr(
        sprite->width,
        sprite->height,
        255,
        255,
        255,
        sprite->frame_delay,
        sprite->animate,
        frames,
        frames_size
    );

    spr_write_to_file(spr, filename);

    spr_free(spr);
}

sprite_T* load_sprite_from_disk(const char* filename)
{
    sprite_T* sprite = (void*) 0;

    spr_T* spr = spr_load_from_file(filename);
    
    if (spr == (void*) 0)
        return (void*) 0;

    dynamic_list_T* textures = init_dynamic_list(sizeof(struct TEXTURE_STRUCT));

    for (int i = 0; i < spr->frames_size; i++)
    {
        spr_frame_T* frame = spr->frames[i];
        unsigned char* img = calloc((spr->width * spr->height) * 4, sizeof(unsigned char));

        int x = 0;
        int y = 0;
        for (int i = 0; i < spr->width * spr->height; i+=1)
        {
            y = i / (int) spr->width;
            x = i % (int) spr->width;

            img[(4 * i)] = frame->pixel_rows[y]->pixels[x]->r;
            img[(4 * i) + 1] = frame->pixel_rows[y]->pixels[x]->g;
            img[(4 * i) + 2] = frame->pixel_rows[y]->pixels[x]->b;
            img[(4 * i) + 3] = frame->pixel_rows[y]->pixels[x]->a;
        }

        texture_T* texture = get_texture_from_data((unsigned char*)img, spr->width, spr->height, GL_RGBA);
        dynamic_list_append(textures, texture);
    }

    sprite = init_sprite(textures, spr->delay, spr->width, spr->height);

    spr_free(spr);

    return sprite;
}
