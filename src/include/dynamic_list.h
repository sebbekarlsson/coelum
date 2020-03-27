#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H
#include <stdlib.h>


typedef struct DYNAMIC_LIST_STRUCT
{
    size_t size;
    size_t item_size;
    void** items;
} dynamic_list_T;

dynamic_list_T* init_dynamic_list(size_t item_size);

void* dynamic_list_append(dynamic_list_T* dynamic_list, void* item);

void dynamic_list_shift_left(dynamic_list_T* dynamic_list, int index);

void dynamic_list_remove(dynamic_list_T* dynamic_list, void* element, void (*free_method)(void* item));

void dynamic_list_free(dynamic_list_T* dynamic_list, void (*free_method)(void* item));
#endif
