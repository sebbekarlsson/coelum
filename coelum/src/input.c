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
    ks->key_locks = calloc(300, sizeof(int));

    keyboard_state_reset(ks);

    return ks;
}

/**
 * Completely reset the keyboard_state.
 *
 * @param keyboard_state_T* keyboard_state
 */
void keyboard_state_reset(keyboard_state_T* keyboard_state)
{
    // fill with zeroes.
    memset(&*keyboard_state->keys, 0, 300 * sizeof(int));
    memset(&*keyboard_state->key_locks, 0, 300 * sizeof(int));
    free(keyboard_state->buffer);
    keyboard_state->buffer = calloc(1, sizeof(char));
    keyboard_state->buffer[0] = '\0';
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

    if (KEYBOARD_STATE->keys[GLFW_KEY_BACKSPACE])
        KEYBOARD_STATE->buffer[strlen(KEYBOARD_STATE->buffer) - 1] = '\0';

    if(
        KEYBOARD_STATE->keys[GLFW_KEY_LEFT_SHIFT] &&
        KEYBOARD_STATE->keys[GLFW_KEY_ESCAPE]
     )
        glfwSetWindowShouldClose(window, 1);
}

/**
 * Used to "stream" user character input to a char* buffer.
 *
 * @param keyboard_state_T* keyboard_state
 * @param char** s - pointer where you want the stream to go.
 */
void keyboard_state_inread(keyboard_state_T* keyboard_state, char **s)
{
    if (*s)
        free(*s);

    *s = calloc(strlen(keyboard_state->buffer) + 1, sizeof(char));
    strcpy(*s, keyboard_state->buffer);
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
    char c = (char) codepoint;
    char* char_str = calloc(2, sizeof(char));

    char_str[0] = c;
    char_str[1] = '\0';
    
    KEYBOARD_STATE->buffer = realloc(KEYBOARD_STATE->buffer, (strlen(KEYBOARD_STATE->buffer) + 2) * sizeof(char));
    strcat(KEYBOARD_STATE->buffer, char_str);

    free(char_str);
}

/**
 * Clear the keyboard_state buffer
 *
 * @param keyboard_state_T* keyboard_state
 */
void keyboard_state_clear_buffer(keyboard_state_T* keyboard_state)
{
    free(keyboard_state->buffer);
    keyboard_state->buffer = calloc(1, sizeof(char));
    keyboard_state->buffer[0] = '\0';
}

/**
 * Replace the keyboard_state buffer with another buffer.
 *
 * @param keyboard_state_T* keyboard_state
 * @param char* buffer
 */
void keyboard_state_copy_buffer(keyboard_state_T* keyboard_state, char* buffer)
{
    if (!buffer)
    {
        free(keyboard_state->buffer);
        keyboard_state->buffer = calloc(1, sizeof(char));
        keyboard_state->buffer[0] = '\0';

        return;
    }

    if (keyboard_state->buffer)
        free(keyboard_state->buffer);

    keyboard_state->buffer = calloc(strlen(buffer) + 1, sizeof(char));
    keyboard_state->buffer[0] = '\0';
    strcpy(keyboard_state->buffer, buffer);
}
