#ifndef HERMES_AST_H
#define HERMES_AST_H
#include <stdio.h>
#include <coelum/dynamic_list.h>

typedef struct AST_STRUCT
{
    enum {
        AST_OBJECT,
        AST_VARIABLE,
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE_ASSIGNMENT,
        AST_FUNCTION_DEFINITION,
        AST_FUNCTION_CALL = 66,
        AST_STRING,
        AST_FLOAT,
        AST_LIST,
        AST_BOOLEAN,
        AST_INTEGER,
        AST_COMPOUND,
        AST_TYPE,
        AST_BINOP,
        AST_NOOP,
        AST_BREAK,
        AST_RETURN,
        AST_IF,
        AST_ELSE,
        AST_WHILE
    } type;
    
    char* function_call_name;

    int int_value;
    unsigned int boolean_value;
    float float_value;
    char* string_value;
    char* type_value;
    char* variable_name;
    struct AST_STRUCT* variable_value;
    struct AST_STRUCT* variable_type;
    char* function_name;
    struct AST_STRUCT* binop_left;
    struct AST_STRUCT* binop_right;
    int binop_operator;
    dynamic_list_T* list_value;
    dynamic_list_T* compound_value;
    dynamic_list_T* function_call_arguments;
    dynamic_list_T* function_definition_arguments;
    struct AST_STRUCT* function_definition_body;
    struct AST_STRUCT* function_definition_type;
    struct AST_STRUCT* if_expr;
    struct AST_STRUCT* if_body;
    struct AST_STRUCT* if_otherwise;
    struct AST_STRUCT* else_expr;
    struct AST_STRUCT* while_expr;
    struct AST_STRUCT* while_body;
    struct AST_STRUCT* return_value;
    
    struct hermes_scope_T* scope;
} AST_T;

AST_T* init_ast(int type);

void ast_set_key_value(AST_T* AST, char* key, void* value);

void* ast_get_value_by_key(AST_T* AST, char* key);

void ast_dump_keys(AST_T* AST);

typedef struct AST_ITEM_STRUCT
{
    char* key;
    void* value;
} AST_item_T;

AST_item_T* init_ast_item(char* key, void* value);
#endif
