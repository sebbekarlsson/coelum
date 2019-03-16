#include <stdio.h>
#include "include/graphics.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/scene_registry.h"


scene_manager* SCENE_MANAGER;


int main(int argc, char* argv[]) {
    printf("Program started\n");

    GLFWwindow* window = setup_graphical_window();

    SCENE_MANAGER = init_scene_manager();
    register_scenes(SCENE_MANAGER);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render here
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();    

    return 0;
}
