#include "include/input.h"
#include <stdio.h>
#include <string.h>


extern keyboard_state* KEYBOARD_STATE;


/**
 * Creates a new keyboard_state
 *
 * @return keyboard_state*
 */
keyboard_state* init_keyboard_state()
{
    keyboard_state* ks = calloc(1, sizeof(struct KEYBOARD_STATE_STRUCT));
    ks->keys = calloc(300, sizeof(int));

    keyboard_state_reset(ks);

    return ks;
}

void keyboard_state_reset(keyboard_state* ks)
{
    // fill with zeroes.
    memset(&*ks->keys, 0, 300 * sizeof(int));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    KEYBOARD_STATE->keys[key] = (int) (glfwGetKey(window, key) == GLFW_PRESS);
}
