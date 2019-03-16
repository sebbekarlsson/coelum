#include "include/dynamic_list.h"


dynamic_list* init_dynamic_list(size_t item_size) {
    dynamic_list* dlist = calloc(1, item_size);
    dlist->item_size = item_size;
    dlist->size = 0;

    return dlist;
}

void append_dynamic_list(dynamic_list* dlist, void* item) {
    dlist->size++;
    dlist->items = realloc(dlist->items, (dlist->size + 1) * dlist->item_size);
    dlist->items[dlist->size - 1] = item;
}

void free_dynamic_list(dynamic_list* dlist) {}
