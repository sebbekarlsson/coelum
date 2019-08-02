#include "include/current.h"


extern theatre_T* THEATRE;


scene_T* get_current_scene()
{
    return scene_manager_get_current_scene(THEATRE->scene_manager);
}

state_T* get_current_state()
{
    return (state_T*) get_current_scene();
}
