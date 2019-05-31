#include "include/hermes_runtime.h"
#include "include/token.h"
#include <string.h>


runtime_T* init_runtime()
{
    runtime_T* runtime = calloc(1, sizeof(struct RUNTIME_STRUCT));
    runtime->scope = init_hermes_scope();

    return runtime;
}

AST_T* runtime_visit(runtime_T* runtime, AST_T* node)
{
    switch (node->type)
    {
        case AST_OBJECT: return runtime_visit_object(runtime, node); break;
        case AST_VARIABLE: return runtime_visit_variable(runtime, node); break;
        case AST_VARIABLE_DEFINITION: return runtime_visit_variable_definition(runtime, node); break;
        case AST_VARIABLE_ASSIGNMENT: return runtime_visit_variable_assignment(runtime, node); break;
        case AST_FUNCTION_DEFINITION: return runtime_visit_function_definition(runtime, node); break;
        case AST_FUNCTION_CALL: return runtime_visit_function_call(runtime, node); break;
        case AST_STRING: return runtime_visit_string(runtime, node); break;
        case AST_FLOAT: return runtime_visit_float(runtime, node); break;
        case AST_LIST: return runtime_visit_list(runtime, node); break;
        case AST_BOOLEAN: return runtime_visit_boolean(runtime, node); break;
        case AST_INTEGER: return runtime_visit_integer(runtime, node); break;
        case AST_COMPOUND: return runtime_visit_compound(runtime, node); break;
        case AST_TYPE: return runtime_visit_type(runtime, node); break;
        case AST_BINOP: return runtime_visit_binop(runtime, node); break;
        case AST_NOOP: return runtime_visit_noop(runtime, node); break;
        case AST_BREAK: return runtime_visit_break(runtime, node); break;
        case AST_RETURN: return runtime_visit_return(runtime, node); break;
        case AST_IF: return runtime_visit_if(runtime, node); break;
        case AST_WHILE: return runtime_visit_while(runtime, node); break;
        default: printf("Uncaught statement %d\n", node->type); exit(1); break;
    }
}

/* ==== helpers ==== */

hermes_scope_T* _get_scope(runtime_T* runtime, AST_T* node)
{
    if (!node->scope)
        return runtime->scope;

    return (hermes_scope_T*) node->scope;
}

unsigned int _boolean_evaluation(AST_T* node)
{
    switch (node->type)
    {
        case AST_INTEGER: return node->int_value > 0; break;
        case AST_FLOAT: return node->float_value > 0; break;
        case AST_BOOLEAN: return node->boolean_value; break;
        case AST_STRING: return strlen(node->string_value) > 0; break;
        default: return 0; break;
    }
}

/* ==== end of helpers ==== */

AST_T* runtime_visit_variable(runtime_T* runtime, AST_T* node)
{
    hermes_scope_T* scope = _get_scope(runtime, node);

    for (int i = 0; i < scope->variable_definitions->size; i++)
    {
        AST_T* variable_definition = (AST_T*) scope->variable_definitions->items[i];

        if (strcmp(variable_definition->variable_name, node->variable_name) == 0)
        {
            return runtime_visit(runtime, variable_definition->variable_value);
        }
    }

    printf("Undefined variable %s\n", node->variable_name); exit(1);
}

AST_T* runtime_visit_variable_definition(runtime_T* runtime, AST_T* node)
{
    dynamic_list_append(_get_scope(runtime, node)->variable_definitions, node);

    return node;
}

AST_T* runtime_visit_variable_assignment(runtime_T* runtime, AST_T* node)
{
    hermes_scope_T* scope = _get_scope(runtime, node);
    AST_T* value = (void*) 0;

    for (int i = 0; i < scope->variable_definitions->size; i++)
    {
        AST_T* ast_variable_definition = (AST_T*) scope->variable_definitions->items[i];

        if (strcmp(ast_variable_definition->variable_name, node->variable_name) == 0)
        {
            value = runtime_visit(runtime, node->variable_value);
            ast_variable_definition->variable_value = value;
        }
    }

    return value;
}

AST_T* runtime_visit_function_definition(runtime_T* runtime, AST_T* node)
{
    dynamic_list_append(_get_scope(runtime, node)->function_definitions, node);

    return node;
}

AST_T* runtime_visit_function_call(runtime_T* runtime, AST_T* node)
{
    hermes_scope_T* scope = _get_scope(runtime, node);

    // TODO: remove this `if` and make a more beautiful implementation of
    // built-in methods.
    if (strcmp(node->function_call_name, "print") == 0)
    {
        for (int x = 0; x < node->function_call_arguments->size; x++)
        {
            AST_T* ast_arg = (AST_T*) node->function_call_arguments->items[x];
            AST_T* visited = runtime_visit(runtime, ast_arg);

            switch (visited->type)
            {
                case AST_STRING: printf("%s\n", visited->string_value); break;
                case AST_INTEGER: printf("%d\n", visited->int_value); break;
                case AST_FLOAT: printf("%0.6f\n", visited->float_value); break;
                case AST_BOOLEAN: printf("%d\n", visited->boolean_value); break;
                case AST_OBJECT: printf("{ object }\n"); break;
            }
        }

        return init_ast(AST_NOOP);
    }

    for (int i = 0; i < scope->function_definitions->size; i++)
    {
        AST_T* function_definition = (AST_T*) scope->function_definitions->items[i];

        hermes_scope_T* function_definition_body_scope = _get_scope(runtime, function_definition->function_definition_body);

        if (strcmp(function_definition->function_name, node->function_call_name) == 0)
        {
            for (int x = 0; x < node->function_call_arguments->size; x++)
            {
                AST_T* ast_arg = (AST_T*) node->function_call_arguments->items[x];

                if (x > function_definition->function_definition_arguments->size - 1)
                {
                    printf("Too many arguments\n");
                    break;
                }

                AST_T* ast_fdef_arg = (AST_T*) function_definition->function_definition_arguments->items[x];
                char* arg_name = ast_fdef_arg->variable_name;

                AST_T* new_variable_def = init_ast(AST_VARIABLE_DEFINITION);
                new_variable_def->variable_value = runtime_visit(runtime, ast_arg);
                new_variable_def->variable_name = arg_name;

                dynamic_list_append(function_definition_body_scope->variable_definitions, new_variable_def);
            }

            return runtime_visit(runtime, function_definition->function_definition_body);
        }
    }

    printf("Undefined method %s\n", node->function_call_name); exit(1);
}

AST_T* runtime_visit_string(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_float(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_object(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_list(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_boolean(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_integer(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_compound(runtime_T* runtime, AST_T* node)
{
    for (int i = 0; i < node->compound_value->size; i++)
    {
        AST_T* child = (AST_T*) node->compound_value->items[i];
        AST_T* visited = runtime_visit(runtime, child);

        if (visited)
        {
            if (visited->type == AST_RETURN)
            {
                if (visited->return_value)
                {
                    return runtime_visit(runtime, visited->return_value);
                }
                else
                {
                    return (void*) 0;
                }
            }
        }
    }

    return node;
}

AST_T* runtime_visit_type(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_binop(runtime_T* runtime, AST_T* node)
{
    AST_T* return_value = (void*) 0;
    AST_T* left = runtime_visit(runtime, node->binop_left);
    AST_T* right = runtime_visit(runtime, node->binop_right);

    switch (node->binop_operator)
    {
        case TOKEN_PLUS: {
            if (left->type == AST_INTEGER && right->type == AST_INTEGER)
            {
                return_value = init_ast(AST_INTEGER);
                return_value->int_value = left->int_value + right->int_value;

                return return_value;
            }
        } break;
        case TOKEN_MINUS: {
            if (left->type == AST_INTEGER && right->type == AST_INTEGER)
            {
                return_value = init_ast(AST_INTEGER);
                return_value->int_value = left->int_value - right->int_value;

                return return_value;
            } 
        } break;
        case TOKEN_DIV: {
            if (left->type == AST_INTEGER && right->type == AST_INTEGER)
            {
                return_value = init_ast(AST_INTEGER);
                return_value->int_value = left->int_value / right->int_value;

                return return_value;
            }
        } break;
        case TOKEN_STAR: {
            if (left->type == AST_INTEGER && right->type == AST_INTEGER)
            {
                return_value = init_ast(AST_INTEGER);
                return_value->int_value = left->int_value * right->int_value;

                return return_value;
            }                 
        } break;
    }

    return node;
}

AST_T* runtime_visit_noop(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_break(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_return(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_if(runtime_T* runtime, AST_T* node)
{
    return node;
}

AST_T* runtime_visit_while(runtime_T* runtime, AST_T* node)
{
    while(_boolean_evaluation(runtime_visit(runtime, node->while_expr)))
    {
        runtime_visit(runtime, node->while_body);
    }

    return node;
}
