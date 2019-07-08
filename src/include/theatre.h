#ifndef COELUM_THEATRE_H
#define COELUM_THEATRE_H
#include "scene_manager.h"
#include "shader_manager.h"
#include "texture_manager.h"
#include "sound.h"


typedef struct THEATRE_STRUCT
{
    scene_manager_T* scene_manager;
    shader_manager_T* shader_manager;
    texture_manager_T* texture_manager;
    AL_T* al;
} theatre_T;

theatre_T* init_theatre();

void theatre_tick(theatre_T* theatre);

void theatre_draw(theatre_T* theatre);

void theatre_free(theatre_T* theatre);
#endif
