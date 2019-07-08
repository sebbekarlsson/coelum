#include "include/theatre.h"


theatre_T* init_theatre()
{
    theatre_T* theatre = calloc(1, sizeof(struct THEATRE_STRUCT));

    theatre->scene_manager = init_scene_manager();
    theatre->shader_manager = init_shader_manager();
    theatre->texture_manager = init_texture_manager();
    theatre->al = init_al();

    return theatre;
}

void theatre_tick(theatre_T* theatre)
{
    scene_manager_tick(theatre->scene_manager);
}

void theatre_draw(theatre_T* theatre)
{
    scene_manager_draw(theatre->scene_manager);
}

void theatre_free(theatre_T* theatre)
{
    printf("Freeing scene_manager...\n");
    scene_manager_free(theatre->scene_manager);

    printf("Freeing shader_manager...\n");
    shader_manager_free(theatre->shader_manager);

    printf("Freeing texture_manager...\n");
    texture_manager_free(theatre->texture_manager);

    printf("Freeing OpenAL...\n");
    al_free(theatre->al);
}
