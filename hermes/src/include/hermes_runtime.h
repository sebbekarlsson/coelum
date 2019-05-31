#ifndef HERMES_RUNTIME_H
#define HERMES_RUNTIME_H
#include "hermes_scope.h"

typedef struct RUNTIME_STRUCT
{
    hermes_scope_T* scope;
} runtime_T;

runtime_T* init_runtime();

AST_T* runtime_visit(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_variable(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_variable_definition(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_variable_assignment(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_function_definition(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_function_call(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_string(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_float(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_object(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_list(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_boolean(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_integer(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_compound(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_type(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_binop(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_noop(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_break(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_return(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_if(runtime_T* runtime, AST_T* node);

AST_T* runtime_visit_while(runtime_T* runtime, AST_T* node);

hermes_scope_T* get_scope(runtime_T* runtime, AST_T* node);
#endif
