#include <coelum/main.h>
#include "include/scene_main.h"
#include "include/colors.h"
#include <coelum/theatre.h>


extern theatre_T* THEATRE;

int main(int argc, char* argv[])
{
    coelum_init();

    scene_manager_register_scene(THEATRE->scene_manager, (scene_T*) init_scene_main());

    if (coelum_main(argc, argv))
    {
        printf("Coelum crashed.");
    }

    return 0;
}
