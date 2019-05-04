#include "include/input.h"
#include <stdio.h>


extern event_manager* EVENT_MANAGER;

/**
 * Creates a new event_manager
 *
 * @return event_manager*
 */
event_manager* init_event_manager()
{
    event_manager* em = calloc(1, sizeof(struct EVENT_MANAGER_STRUCT));
    em->event_listeners = init_dynamic_list(sizeof(struct EVENT_LISTENER_STRUCT));

    return em;
}

/**
 * Adds an event listener to an event_manager
 *
 * @param event_manager* em
 * @param int key - key to listen for
 * @param void(*callback)() - function to be called when event is emitted
 */
void add_event_listener(event_manager* em, int key, void (*callback)())
{
    event_listener* el = calloc(1, sizeof(struct EVENT_LISTENER_STRUCT));
    el->key = key;
    el->callback = callback;

    dynamic_list_append(em->event_listeners, el);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    for (int i = 0; i < EVENT_MANAGER->event_listeners->size; i++)
    {
        event_listener* el = (event_listener*) EVENT_MANAGER->event_listeners->items[i];

        if (key == el->key)
            el->callback(glfwGetKey(window, el->key));
    }
}
