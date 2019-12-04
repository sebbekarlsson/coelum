#include "include/window.h"
#include "include/constants.h"
#include <GLFW/glfw3.h>
#include <stdio.h>


extern volatile unsigned int window_width;
extern volatile unsigned int window_height;


/**
 * Use this to create a window with OpenGL context
 *
 * @return GLFWwindow*
 */
GLFWwindow* setup_graphical_window(int width, int height)
{
    window_width = width;
    window_height = height;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

    return window;
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
    window_width = width;
    window_height = height;
    // glViewport((width / 2) - (WINDOW_WIDTH / 2), (height / 2) - (WINDOW_HEIGHT / 2), 640, 480);
}
