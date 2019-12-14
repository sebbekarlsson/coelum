#ifndef COELUM_WINDOW_H
#define COELUM_WINDOW_H
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


typedef struct WINDOW_STATE_STRUCT
{
    unsigned int window_width;
    unsigned int window_height;
    unsigned int blit_w;
    unsigned int blit_h;
    unsigned int blit_start_x;
    unsigned int blit_start_y;
    GLFWwindow* window;
} window_state_T;

window_state_T* setup_graphical_window(int width, int height);

void window_state_free(window_state_T* window_state);

void window_state_recalc(window_state_T* window_state, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
#endif
