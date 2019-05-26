#include "include/AST.h"
#include <stdlib.h>
#include <string.h>


AST_T* init_ast(char* type_name)
{
    AST_T* AST = calloc(1, sizeof(struct AST_STRUCT));
    AST->type_name = type_name;
    AST->size = 0;

    return AST;
}

void ast_set_key_value(AST_T* AST, char* key, void* value)
{
    AST_item_T* item = init_ast_item(key, value);
    AST->size++;
    AST->items = realloc(AST->items, AST->size + sizeof(value));
    AST->items[AST->size - 1] = item;
}

void* ast_get_value_by_key(AST_T* AST, char* key)
{
    for (int i = 0; i < AST->size; i++)
    {
        AST_item_T* item = (AST_item_T*) AST->items[i];

        if (strcmp(item->key, key) == 0)
            return item->value;
    }

    return (void*) 0;
}

AST_item_T* init_ast_item(char* key, void* value)
{
    AST_item_T* item = calloc(1, sizeof(struct AST_ITEM_STRUCT));
    item->key = key;
    item->value = value;

    return item;
}
