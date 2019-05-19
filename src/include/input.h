#ifndef COELUM_INPUT_H
#define COELUM_INPUT_H
#include <GLFW/glfw3.h>
#include "dynamic_list.h"


typedef struct KEYBOARD_STATE_STRUCT
{
    int* keys;
} keyboard_state;

keyboard_state* init_keyboard_state();

void keyboard_state_reset(keyboard_state* ks);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif
