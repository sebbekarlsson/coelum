#include "include/window.h"
#include "include/constants.h"
#include "include/config.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>


extern config_T* CONFIG;
extern window_state_T* WINDOW_STATE;


/**
 * Use this to create a window with OpenGL context
 *
 * @return window_state_T*
 */
window_state_T* setup_graphical_window(int width, int height)
{
    window_state_T* window_state = calloc(1, sizeof(struct WINDOW_STATE_STRUCT));

    window_state->window_width = width;
    window_state->window_height = height;
    window_state->window_width = 0;
    window_state->window_height = 0;
    window_state->blit_w = 0;
    window_state->blit_h = 0;
    window_state->blit_start_x = 0;
    window_state->blit_start_y = 0;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, CONFIG->window_resizable ? GL_TRUE : GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(width, height, "coelum", NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return NULL;
    }

    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    window_state->window = window;

    return window_state;
}

void window_state_free(window_state_T* window_state)
{
    glfwDestroyWindow(window_state->window);
    free(window_state);
}

/**
 * Called when the window is resized.
 *
 * @param GLFWwindow* window
 * @param int width
 * @param int height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    WINDOW_STATE->window_width = width;
    WINDOW_STATE->window_height = height;
    WINDOW_STATE->blit_w = WINDOW_STATE->window_height * ((float)RES_WIDTH) / ((float)RES_HEIGHT);
    WINDOW_STATE->blit_h = WINDOW_STATE->window_height;
    WINDOW_STATE->blit_start_x = (WINDOW_STATE->window_width / 2) - (WINDOW_STATE->blit_w / 2);
    WINDOW_STATE->blit_start_y = 0;
    
    // glViewport((width / 2) - (WINDOW_WIDTH / 2), (height / 2) - (WINDOW_HEIGHT / 2), 640, 480);
}
