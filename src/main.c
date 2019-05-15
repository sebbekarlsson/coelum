#include <stdio.h>
#include "include/graphics.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/scene_registry.h"
#include "include/shader_manager.h"
#include "include/shader_registry.h"
#include "include/texture_manager.h"
#include "include/texture_registry.h"
#include "include/sound.h"


keyboard_state* KEYBOARD_STATE;
shader_manager* SHADER_MANAGER;
texture_manager* TEXTURE_MANAGER;
scene_manager* SCENE_MANAGER;

GLFWwindow* window = (void*) 0;

int main(int argc, char* argv[])
{ 
    printf("Program started\n");

    window = setup_graphical_window(640, 480);

    init_al();

    SHADER_MANAGER = init_shader_manager();
    register_shader_programs(SHADER_MANAGER);

    TEXTURE_MANAGER = init_texture_manager();
    register_textures(TEXTURE_MANAGER);

    KEYBOARD_STATE = init_keyboard_state();
    glfwSetKeyCallback(window, key_callback);

    SCENE_MANAGER = init_scene_manager();
    register_scenes(SCENE_MANAGER); 

    while(!glfwWindowShouldClose(window))
    {
        if (SCENE_MANAGER->scene_index == -1)
            scene_manager_next(SCENE_MANAGER);

        glfwPollEvents();

        glClearColor(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render here
        scene_manager_tick(SCENE_MANAGER);
        scene_manager_draw(SCENE_MANAGER);
        
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    exit_al(); 

    return 0;
}
