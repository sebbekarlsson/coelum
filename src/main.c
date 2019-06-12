#include <stdio.h>
#include "include/main.h"
#include "include/constants.h"
#include "include/window.h"
#include "include/input.h"
#include "include/theatre.h"
#include "include/scene_registry.h"
#include "include/shader_registry.h"
#include "include/texture_manager.h"
#include "include/texture_registry.h"
#include "include/sound.h"


keyboard_state_T* KEYBOARD_STATE;
mouse_state_T* MOUSE_STATE;
theatre_T* THEATRE;

GLFWwindow* window = (void*) 0;

void coelum_init()
{
    printf("Coelum is being initialized...\n");

    window = setup_graphical_window(WINDOW_WIDTH, WINDOW_HEIGHT);

    THEATRE = init_theatre();
    register_shader_programs(THEATRE->shader_manager);
    register_textures(THEATRE->texture_manager);
    register_scenes(THEATRE->scene_manager);

    KEYBOARD_STATE = init_keyboard_state();
    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, character_callback);

    MOUSE_STATE = init_mouse_state();
    glfwSetCursorPosCallback(window, cursor_position_callback);

    printf("Coelum was initialized.\n");
}

int coelum_main(int argc, char* argv[])
{ 
    while(!glfwWindowShouldClose(window) && THEATRE->scene_manager->scenes->size > 0)
    {
        if (THEATRE->scene_manager->scene_index == -1)
            scene_manager_next(THEATRE->scene_manager);

        scene_T* scene = scene_manager_get_current_scene(THEATRE->scene_manager);
        state_T* state = (state_T*) scene;

        MOUSE_STATE->dx = 0.0f;
        MOUSE_STATE->dy = 0.0f;

        glfwPollEvents();

        glClearColor(scene->bg_r / 255.0f, scene->bg_g / 255.0f, scene->bg_b / 255.0f, 1.0f);

        if (state->camera->projection_view->dimensions == 2)
        { // we are doing 2D
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        else
        { // we are doing 3D
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        glfwSetInputMode(window, GLFW_CURSOR, MOUSE_STATE->input_mode);

        theatre_tick(THEATRE);
        theatre_draw(THEATRE);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    al_free(THEATRE->al);

    return 0;
}
