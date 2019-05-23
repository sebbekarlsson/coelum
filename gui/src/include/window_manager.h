#ifndef COELUMG_WINDOW_MANAGER_H
#define COELUMG_WINDOW_MANAGER_H
#include <coelum/dynamic_list.h>


typedef struct WINDOW_MANAGER_STRUCT
{
    dynamic_list_T* windows;
} window_manager_T;

window_manager_T* init_window_manager();

void window_manager_tick(window_manager_T* window_manager);

void window_manager_draw(window_manager_T* window_manager);
#endif
