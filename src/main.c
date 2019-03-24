#include <stdio.h>
#include "include/graphics.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/scene_registry.h"
#include "include/shader_manager.h"
#include "include/shader_registry.h"


shader_manager* SHADER_MANAGER;
event_manager* EVENT_MANAGER;
scene_manager* SCENE_MANAGER;


int main(int argc, char* argv[]) {
    printf("Program started\n");

    GLFWwindow* window = setup_graphical_window();

    SHADER_MANAGER = init_shader_manager();
    register_shader_programs(SHADER_MANAGER);

    EVENT_MANAGER = init_event_manager();
    glfwSetKeyCallback(window, key_callback);

    SCENE_MANAGER = init_scene_manager();
    register_scenes(SCENE_MANAGER); 

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render here
        scene_manager_tick(SCENE_MANAGER);
        scene_manager_draw(SCENE_MANAGER);
        
        glfwSwapBuffers(window);
    }

    glfwTerminate();    

    return 0;
}
