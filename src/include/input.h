#ifndef PONG_INPUT_H
#define PONG_INPUT_H
#include <GLFW/glfw3.h>
#include "dynamic_list.h"


typedef struct EVENT_LISTENER_STRUCT {
    int key;
    int enabled;
    void (*callback)();
} event_listener;

typedef struct EVENT_MANAGER_STRUCT {
    dynamic_list* event_listeners;
} event_manager;

event_manager* init_event_manager();

event_listener* add_event_listener(event_manager* em, int key, void (*callback)());

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif
