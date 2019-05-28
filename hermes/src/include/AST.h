#ifndef HERMES_AST_H
#define HERMES_AST_H
#include <stdio.h>

typedef struct AST_STRUCT
{
    char* type_name;
    void** items;
    size_t size;
} AST_T;

AST_T* init_ast(char* type_name);

void ast_set_key_value(AST_T* AST, char* key, void* value);

void* ast_get_value_by_key(AST_T* AST, char* key);

typedef struct AST_ITEM_STRUCT
{
    char* key;
    void* value;
} AST_item_T;

AST_item_T* init_ast_item(char* key, void* value);
#endif
