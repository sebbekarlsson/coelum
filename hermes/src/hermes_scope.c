#include "include/hermes_scope.h"


hermes_scope_T* init_hermes_scope()
{
    hermes_scope_T* hermes_scope = calloc(1, sizeof(struct HERMES_SCOPE_STRUCT));
    hermes_scope->variable_definitions = init_dynamic_list(sizeof(struct AST_STRUCT));
    hermes_scope->function_definitions = init_dynamic_list(sizeof(struct AST_STRUCT));

    return hermes_scope;
}
