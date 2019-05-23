#ifndef COELUM_INPUT_H
#define COELUM_INPUT_H
#include <GLFW/glfw3.h>
#include "dynamic_list.h"


typedef struct KEYBOARD_STATE_STRUCT
{
    unsigned int* keys;
    char* buffer; 
} keyboard_state_T;

keyboard_state_T* init_keyboard_state();

void keyboard_state_reset(keyboard_state_T* keyboard_state);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void character_callback(GLFWwindow* window, unsigned int codepoint);
#endif
