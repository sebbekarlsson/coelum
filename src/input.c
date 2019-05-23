#include "include/input.h"
#include <stdio.h>
#include <string.h>


extern keyboard_state_T* KEYBOARD_STATE;


/**
 * Creates a new keyboard_state
 *
 * @return keyboard_state_T*
 */
keyboard_state_T* init_keyboard_state()
{
    keyboard_state_T* ks = calloc(1, sizeof(struct KEYBOARD_STATE_STRUCT));
    ks->keys = calloc(300, sizeof(int));
    ks->buffer = calloc(1, sizeof(char));
    ks->buffer[0] = '\0';

    keyboard_state_reset(ks);

    return ks;
}

void keyboard_state_reset(keyboard_state_T* keyboard_state)
{
    // fill with zeroes.
    memset(&*keyboard_state->keys, 0, 300 * sizeof(int));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    KEYBOARD_STATE->keys[key] = (int) (glfwGetKey(window, key) == GLFW_PRESS);

    if (KEYBOARD_STATE->keys[GLFW_KEY_BACKSPACE])
    {
        free(KEYBOARD_STATE->buffer);
        KEYBOARD_STATE->buffer = calloc(1, sizeof(char));
        KEYBOARD_STATE->buffer[0] = '\0';
    }
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    char c = (char) codepoint;
    char* char_str = calloc(2, sizeof(char));

    char_str[0] = c;
    char_str[1] = '\0';
    
    KEYBOARD_STATE->buffer = realloc(KEYBOARD_STATE->buffer, (strlen(KEYBOARD_STATE->buffer) + 2) * sizeof(char));
    strcat(KEYBOARD_STATE->buffer, char_str);

    free(char_str);
}
