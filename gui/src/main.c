#include <coelum/main.h>
#include <coelum/theatre.h>
#include "include/scene_main.h"
#include "include/colors.h"


extern theatre_T* THEATRE;

int main(int argc, char* argv[])
{
    coelum_init();

    scene_manager_register_scene(THEATRE->scene_manager, (scene_T*) init_scene_main());

    return coelum_main(argc, argv);
}
