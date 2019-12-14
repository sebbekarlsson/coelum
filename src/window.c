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
    window_state_recalc(window_state, width, height);

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

void window_state_recalc(window_state_T* window_state, int width, int height)
{
    window_state->window_width = width;
    window_state->window_height = height;
    window_state->blit_w = window_state->window_height * ((float)RES_WIDTH) / ((float)RES_HEIGHT);
    window_state->blit_h = window_state->window_height;
    window_state->blit_start_x = (window_state->window_width / 2) - (window_state->blit_w / 2);
    window_state->blit_start_y = 0;

    printf("window_width: %d\n", window_state->window_width);
    printf("window_height: %d\n", window_state->window_height);
    printf("window_blit_w: %d\n", window_state->blit_w);
    printf("window_blit_h: %d\n", window_state->blit_h);
    printf("window_blit_start_x: %d\n", window_state->blit_start_x);
    printf("window_blit_start_y: %d\n", window_state->blit_start_y);
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
    window_state_recalc(WINDOW_STATE, width, height);
    // glViewport((width / 2) - (WINDOW_WIDTH / 2), (height / 2) - (WINDOW_HEIGHT / 2), 640, 480);
}
