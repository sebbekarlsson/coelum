#include "include/theatre.h"


theatre_T* init_theatre()
{
    theatre_T* theatre = calloc(1, sizeof(struct THEATRE_STRUCT));

    theatre->scene_manager = init_scene_manager();
    theatre->shader_manager = init_shader_manager();
    theatre->texture_manager = init_texture_manager();

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
