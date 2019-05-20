#ifndef COELUM_DYNAMIC_LIST_H
#define COELUM_DYNAMIC_LIST_H
#include <stdlib.h>


typedef struct DYNAMIC_LIST_STRUCT {
    size_t size;
    size_t item_size;
    void** items;
} dynamic_list_T;

dynamic_list_T* init_dynamic_list(size_t item_size);

void dynamic_list_append(dynamic_list_T* dlist, void* item);

void dynamic_list_free(dynamic_list_T* dlist);
#endif
