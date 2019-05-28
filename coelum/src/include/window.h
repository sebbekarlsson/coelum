#ifndef COELUM_WINDOW_H
#define COELUM_WINDOW_H
#include <glad/glad.h> 
#include <GLFW/glfw3.h>


GLFWwindow* setup_graphical_window(int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
#endif
