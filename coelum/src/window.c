#include "include/window.h"
#include "include/constants.h"
#include <GLFW/glfw3.h>
#include <stdio.h>


/**
 * Use this to create a window with OpenGL context
 *
 * @return GLFWwindow*
 */
GLFWwindow* setup_graphical_window(int width, int height)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(width, height, "cpong", NULL, NULL);

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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    glViewport((width / 2) - (WINDOW_WIDTH / 2), (height / 2) - (WINDOW_HEIGHT / 2), 640, 480);
}
