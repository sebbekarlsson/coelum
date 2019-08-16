#ifndef COELUM_INPUT_H
#define COELUM_INPUT_H
#include <GLFW/glfw3.h>
#include "dynamic_list.h"


typedef struct KEYBOARD_STATE_STRUCT
{
    unsigned int* keys; // all possible keys, on / off
    unsigned int* key_locks;
    char character;
} keyboard_state_T;

typedef struct MOUSE_STATE_STRUCT
{
    double x;
    double y;
    float dx;
    float dy;
    int input_mode;
    unsigned int button_left;
    unsigned int button_right;
} mouse_state_T;

mouse_state_T* init_mouse_state();

keyboard_state_T* init_keyboard_state();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void character_callback(GLFWwindow* window, unsigned int codepoint);

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void keyboard_state_free(keyboard_state_T* keyboard_state);

void mouse_state_free(mouse_state_T* mouse_state);
#endif
