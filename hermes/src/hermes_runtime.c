#include "include/hermes_runtime.h"
#include "include/token.h"
#include <string.h>


runtime_T* init_runtime()
{
    runtime_T* runtime = calloc(1, sizeof(struct RUNTIME_STRUCT));
    runtime->scope = init_hermes_scope();
    runtime->references = init_dynamic_list(sizeof(struct RUNTIME_REFERENCE_STRUCT));

    return runtime;
}

runtime_reference_T* init_runtime_reference()
{
    runtime_reference_T* runtime_reference = calloc(1, sizeof(struct RUNTIME_REFERENCE_STRUCT));
    runtime_reference->object = init_ast(AST_OBJECT);
    runtime_reference->object->object_children = init_dynamic_list(sizeof(struct AST_STRUCT));

    return runtime_reference;
}

runtime_reference_T* runtime_get_reference(runtime_T* runtime, char* variable_name)
{
    for (int i = 0; i < runtime->references->size; i++)
    {
        runtime_reference_T* reference = (runtime_reference_T*) runtime->references->items[i];

        if (strcmp(reference->object->variable_name, variable_name) == 0)
            return reference;
    }

    return (void*) 0;
}

runtime_reference_T* runtime_register_reference(runtime_T* runtime, runtime_reference_T* runtime_reference)
{
    dynamic_list_append(runtime->references, runtime_reference);

    return runtime_reference;
}

AST_T* runtime_visit(runtime_T* runtime, AST_T* node)
{
    if (!node)
        return (void*) 0;

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
        case AST_ATTRIBUTE_ACCESS: return runtime_visit_attribute_access(runtime, node); break;
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
    hermes_scope_T* scope = get_scope(runtime, node);

    for (int i = 0; i < scope->variable_definitions->size; i++)
    {
        AST_T* variable_definition = (AST_T*) scope->variable_definitions->items[i];

        if (strcmp(variable_definition->variable_name, node->variable_name) == 0)
        {
            if (!variable_definition->variable_value)
                return variable_definition;

            return runtime_visit(runtime, variable_definition->variable_value);
        }
    }

    printf("Undefined variable %s\n", node->variable_name); exit(1);
}

AST_T* runtime_visit_variable_definition(runtime_T* runtime, AST_T* node)
{
    if (node->variable_value)
        node->variable_value = runtime_visit(runtime, node->variable_value);

    dynamic_list_append(get_scope(runtime, node)->variable_definitions, node);

    return node;
}

AST_T* runtime_visit_variable_assignment(runtime_T* runtime, AST_T* node)
{
    hermes_scope_T* scope = get_scope(runtime, node);
    AST_T* value = (void*) 0;

    AST_T* left = node->variable_assignment_left;
    hermes_scope_T* variable_scope = get_scope(runtime, node);

    for (int i = 0; i < variable_scope->variable_definitions->size; i++)
    {
        AST_T* ast_variable_definition = (AST_T*) variable_scope->variable_definitions->items[i];

        if (strcmp(ast_variable_definition->variable_name, left->variable_name) == 0)
        {
            value = runtime_visit(runtime, node->variable_value);
            ast_variable_definition->variable_value = value;
            return value;
        }
    }

    printf("Cant set undefined variable `%s`\n", node->variable_name); exit(1);
}

AST_T* runtime_visit_function_definition(runtime_T* runtime, AST_T* node)
{
    dynamic_list_append(get_scope(runtime, node)->function_definitions, node);

    return node;
}

AST_T* runtime_visit_function_call(runtime_T* runtime, AST_T* node)
{
    hermes_scope_T* scope = get_scope(runtime, node);

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

        hermes_scope_T* function_definition_body_scope = get_scope(runtime, function_definition->function_definition_body);

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
    for (int i = 0; i < node->object_children->size; i++)
    {
        AST_T* child = (AST_T*) node->object_children->items[i];
        node->object_children->items[i] = runtime_visit(runtime, child);
    }

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

        if (!child)
            continue;

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

AST_T* runtime_visit_attribute_access(runtime_T* runtime, AST_T* node)
{
    AST_T* left = runtime_visit(runtime, node->binop_left);

    node->scope = (struct hermes_scope_T*) get_scope(runtime, left);
    node->binop_right->scope = node->scope;

    return runtime_visit(runtime, node->binop_right);
}

AST_T* runtime_visit_binop(runtime_T* runtime, AST_T* node)
{
    AST_T* return_value = (void*) 0;
    AST_T* left = runtime_visit(runtime, node->binop_left);
    AST_T* right = node->binop_right;

    if (node->binop_operator == TOKEN_DOT)
    {
        char* access_name = (void*) 0;

        switch (right->type)
        {
            case AST_VARIABLE: access_name = right->variable_name; break;
            case AST_FUNCTION_CALL: access_name = right->function_call_name; break;
        }

        if (left->type == AST_VARIABLE_DEFINITION)
        {
            if (strcmp(left->variable_type->type_value, "ref") == 0)
            {
                runtime_reference_T* reference = runtime_get_reference(runtime, left->variable_name);

                if (!reference)
                {
                    printf("The reference `%s` is not registered in the current runtime.\n", left->variable_name);
                    exit(1);
                }
                else
                {
                    left = reference->object;
                }
            }
        }

        if (right->type == AST_BINOP)
            right = runtime_visit(runtime, right);
        
        if (left->type == AST_OBJECT)
        {
            for (int i = 0; i < left->object_children->size; i++)
            {
                AST_T* child = runtime_visit(runtime, (AST_T*) left->object_children->items[i]);

                if (child->type == AST_VARIABLE_DEFINITION && right->type == AST_VARIABLE_ASSIGNMENT)
                {
                    child->variable_value = runtime_visit(runtime, right->variable_value);
                    return child->variable_value;
                }

                if (child->type == AST_VARIABLE_DEFINITION)
                {
                    if (strcmp(child->variable_name, access_name) == 0)
                    {
                        if (child->variable_value)
                        {
                            return runtime_visit(runtime, child->variable_value);
                        }
                        else
                        {
                            return child;
                        }
                    }
                }
                else
                if (child->type == AST_FUNCTION_DEFINITION)
                {
                    if (strcmp(child->function_name, access_name) == 0)
                    {
                        for (int x = 0; x < right->function_call_arguments->size; x++)
                        {
                            AST_T* ast_arg = (AST_T*) right->function_call_arguments->items[x];

                            if (x > child->function_definition_arguments->size - 1)
                            {
                                printf("Too many arguments\n");
                                break;
                            }

                            AST_T* ast_fdef_arg = (AST_T*) child->function_definition_arguments->items[x];
                            char* arg_name = ast_fdef_arg->variable_name;

                            AST_T* new_variable_def = init_ast(AST_VARIABLE_DEFINITION);
                            new_variable_def->variable_value = runtime_visit(runtime, ast_arg);
                            new_variable_def->variable_name = arg_name;

                            dynamic_list_append(get_scope(runtime, child->function_definition_body)->variable_definitions, new_variable_def);
                        }
                        return runtime_visit(runtime, child->function_definition_body);
                    }
                }
            }
        }
    }

    right = runtime_visit(runtime, right);

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

hermes_scope_T* get_scope(runtime_T* runtime, AST_T* node)
{
    if (!node->scope)
        return runtime->scope;

    return (hermes_scope_T*) node->scope;
}
