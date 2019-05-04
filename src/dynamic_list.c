#include "include/dynamic_list.h"


/**
 * Creates a new list.
 * The item_size argument is used to define how big every item in the list
 * shall be.
 *
 * @param size_t item_size
 */
dynamic_list* init_dynamic_list(size_t item_size)
{
    dynamic_list* dlist = calloc(1, sizeof(struct DYNAMIC_LIST_STRUCT));
    dlist->item_size = item_size;
    dlist->size = 0;

    return dlist;
}

/**
 * Appends and item to a dynamic_list
 *
 * @param dynamic_list* dlist
 * @param void* item
 */
void dynamic_list_append(dynamic_list* dlist, void* item)
{
    dlist->size++;
    dlist->items = realloc(dlist->items, (dlist->size + 1) * dlist->item_size);
    dlist->items[dlist->size - 1] = item;
}

/**
 * Use this to free / deallocate a dynamic_list.
 *
 * @param dynamic_list* dlist
 */
void dynamic_list_free(dynamic_list* dlist)
{
    // silence
}
