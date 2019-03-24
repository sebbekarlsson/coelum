#ifndef PONG_INPUT_H
#define PONG_INPUT_H
#include <GLFW/glfw3.h>
#include "dynamic_list.h"

typedef struct EVENT_LISTENER_STRUCT {
    int key;
    void (*callback)();
} event_listener;

typedef struct EVENT_MANAGER_STRUCT {
    dynamic_list* event_listeners;
} event_manager;

event_manager* init_event_manager();

void add_event_listener(event_manager* em, int key, void (*callback)());

void processInput(GLFWwindow *window);
#endif
