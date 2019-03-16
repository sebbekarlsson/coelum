#include <stdio.h>
#include "include/graphics.h"
#include "include/scene_manager.h"
#include "include/scene_registry.h"


scene_manager* SCENE_MANAGER;


int main(int argc, char* argv[]) {
    printf("Program started\n");

    setup_graphics();

    SCENE_MANAGER = init_scene_manager();
    register_scenes(SCENE_MANAGER);

    return 0;
}
