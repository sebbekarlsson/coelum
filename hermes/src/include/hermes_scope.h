#ifndef HERMES_SCOPE_H
#define HERMES_SCOPE_H
#include "AST.h"
#include <coelum/dynamic_list.h>


typedef struct HERMES_SCOPE_STRUCT
{
    AST_T* owner;
    dynamic_list_T* variable_definitions;
    dynamic_list_T* function_definitions;
} hermes_scope_T;

hermes_scope_T* init_hermes_scope();
#endif
