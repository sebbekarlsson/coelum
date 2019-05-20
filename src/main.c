#include <stdio.h>
#include "include/main.h"
#include "include/constants.h"
#include "include/window.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/scene_registry.h"
#include "include/shader_manager.h"
#include "include/shader_registry.h"
#include "include/texture_manager.h"
#include "include/texture_registry.h"
#include "include/sound.h"
#include "include/dev_gui.h"


keyboard_state_T* KEYBOARD_STATE;
shader_manager_T* SHADER_MANAGER;
texture_manager_T* TEXTURE_MANAGER;
scene_manager_T* SCENE_MANAGER;

GLFWwindow* window = (void*) 0;

void coelum_init()
{
    printf("Coelum is being initialized...\n");

    window = setup_graphical_window(WINDOW_WIDTH, WINDOW_HEIGHT);

    init_al();

    SHADER_MANAGER = init_shader_manager();
    register_shader_programs(SHADER_MANAGER);

    TEXTURE_MANAGER = init_texture_manager();
    register_textures(TEXTURE_MANAGER);

    KEYBOARD_STATE = init_keyboard_state();
    glfwSetKeyCallback(window, key_callback);

    SCENE_MANAGER = init_scene_manager();
    register_scenes(SCENE_MANAGER);

    printf("Coelum was initialized.\n");
}

int coelum_main(int argc, char* argv[], int dev_mode)
{ 
    while(!glfwWindowShouldClose(window) &&  SCENE_MANAGER->scenes->size > 0)
    {
        if (SCENE_MANAGER->scene_index == -1)
            scene_manager_next(SCENE_MANAGER);

        glfwPollEvents();

        glClearColor(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); 

        scene_manager_tick(SCENE_MANAGER); 
        scene_manager_draw(SCENE_MANAGER);

        if (dev_mode)
        {
            dev_gui_tick();
            dev_gui_draw();
        }
        
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    exit_al(); 

    return 0;
}
