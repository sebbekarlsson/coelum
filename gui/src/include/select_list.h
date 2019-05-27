#ifndef COELUMG_SELECT_LIST_H
#define COELUMG_SELECT_LIST_H
#include "window.h"
#include "window_component.h"
#include <coelum/dynamic_list.h>
#include <glad/glad.h> 


typedef struct SELECT_LIST_ITEM_STRUCT
{
    char* key;
    char* value;
} select_list_item_T;

select_list_item_T* init_select_list_item(char* key, char* value);

typedef struct SELECT_LIST_STRUCT
{
    window_component_T base;
    unsigned int selected_index;
    dynamic_list_T* items;
    float width;
    float height;
    float scroll_position;
    window_T* window;
} select_list_T;

select_list_T* init_select_list(float x, float y, float width, float height, dynamic_list_T* items, window_T* window);

void select_list_tick(actor_T* self);

void select_list_draw(actor_T* self);

select_list_item_T* select_list_get_selected_item(select_list_T* select_list);
#endif
