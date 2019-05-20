/**
 * TODO: add dynamic_list_remove method to remove items from list
 */
#include "include/dynamic_list.h"


/**
 * Creates a new list.
 * The item_size argument is used to define how big every item in the list
 * shall be.
 *
 * @param size_t item_size
 */
dynamic_list_T* init_dynamic_list(size_t item_size)
{
    dynamic_list_T* dynamic_list = calloc(1, sizeof(struct DYNAMIC_LIST_STRUCT));
    dynamic_list->item_size = item_size;
    dynamic_list->size = 0;

    return dynamic_list;
}

/**
 * Appends and item to a dynamic_list
 *
 * @param dynamic_list_T* dynamic_list
 * @param void* item
 */
void dynamic_list_append(dynamic_list_T* dynamic_list, void* item)
{
    dynamic_list->size++;
    dynamic_list->items = realloc(dynamic_list->items, (dynamic_list->size + 1) * dynamic_list->item_size);
    dynamic_list->items[dynamic_list->size - 1] = item;
}

/**
 * Use this to free / deallocate a dynamic_list.
 *
 * @param dynamic_list_T* dynamic_list
 */
void dynamic_list_free(dynamic_list_T* dynamic_list)
{
    // silence
}
