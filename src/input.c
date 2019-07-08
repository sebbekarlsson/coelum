#include "include/input.h"
#include <stdio.h>
#include <string.h>


extern keyboard_state_T* KEYBOARD_STATE;
extern mouse_state_T* MOUSE_STATE;


mouse_state_T* init_mouse_state()
{
    mouse_state_T* mouse_state = calloc(1, sizeof(struct MOUSE_STATE_STRUCT));
    mouse_state->x = 0;
    mouse_state->y = 0;
    mouse_state->dx = 0;
    mouse_state->dy = 0;
    mouse_state->input_mode = GLFW_CURSOR_NORMAL;

    return mouse_state;
}
/**
 * Creates a new keyboard_state
 *
 * @return keyboard_state_T*
 */
keyboard_state_T* init_keyboard_state()
{
    keyboard_state_T* keyboard_state = calloc(1, sizeof(struct KEYBOARD_STATE_STRUCT));
    keyboard_state->keys = calloc(300, sizeof(unsigned int));
    keyboard_state->key_locks = calloc(300, sizeof(unsigned int));

    memset(&*keyboard_state->keys, 0, 300 * sizeof(int));
    memset(&*keyboard_state->key_locks, 0, 300 * sizeof(int));
    keyboard_state->character = 0;

    return keyboard_state;
}

/**
 * Callback for when user is pressing a key on the keyboard
 * (should not be called by anyone except glfw).
 *
 * @param GLFWwindow* window
 * @param int key
 * @param int scancode
 * @param int action
 * @param int mods
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (KEYBOARD_STATE->key_locks[key] == 1)
    {
        KEYBOARD_STATE->keys[key] = 0;
        KEYBOARD_STATE->key_locks[key] = 0;
        return;
    } 

    KEYBOARD_STATE->keys[key] = (int) (glfwGetKey(window, key) == GLFW_PRESS);

    if(
        KEYBOARD_STATE->keys[GLFW_KEY_LEFT_SHIFT] &&
        KEYBOARD_STATE->keys[GLFW_KEY_ESCAPE]
     )
        glfwSetWindowShouldClose(window, 1);
}

/**
 * Callback for when user is typing characters
 * (should not be called by anyone except glfw).
 *
 * @param GLFWwindow* window
 * @param unsigned int codepoint
 */
void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    KEYBOARD_STATE->character = (char) codepoint;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    MOUSE_STATE->dx = MOUSE_STATE->x - xpos;
    MOUSE_STATE->x = xpos;
    MOUSE_STATE->dy = MOUSE_STATE->y - ypos;
    MOUSE_STATE->y = ypos;
}
