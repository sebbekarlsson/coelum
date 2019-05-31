#include "include/hermes_parser.h"
#include <string.h>


const char* DATA_TYPE_VOID = "void";
const char* DATA_TYPE_STRING = "string";
const char* DATA_TYPE_INT = "int";
const char* DATA_TYPE_FLOAT = "float";
const char* DATA_TYPE_BOOLEAN = "bool";
const char* DATA_TYPE_OBJECT = "object";

const char* STATEMENT_WHILE = "while";
const char* STATEMENT_IF = "if";
const char* STATEMENT_ELSE = "else";
const char* STATEMENT_RETURN = "return";

const char* VALUE_FALSE = "false";
const char* VALUE_TRUE = "true";

hermes_parser_T* init_hermes_parser(lexer_T* lexer)
{
    hermes_parser_T* hermes_parser = calloc(1, sizeof(struct HERMES_PARSER_STRUCT));
    hermes_parser->lexer = lexer;
    hermes_parser->current_token = lexer_get_next_token(hermes_parser->lexer);
}

// etc

AST_T* hermes_parser_parse(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    return hermes_parser_parse_statements(hermes_parser, scope);
}

AST_T* hermes_parser_eat(hermes_parser_T* hermes_parser, int token_type)
{
    if (hermes_parser->current_token->type != token_type)
    {
        printf(
            "Unexpected token `%s`, was expecting `%d`.\n",
            hermes_parser->current_token->value,
            token_type
        );
        exit(1);
    }
    else if (hermes_parser->current_token->type == token_type)
    {
        hermes_parser->prev_token = hermes_parser->current_token;
        hermes_parser->current_token = lexer_get_next_token(hermes_parser->lexer);
    }
}

AST_T* hermes_parser_parse_statement(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    switch (hermes_parser->current_token->type)
    {
        case TOKEN_ID: {
            char* token_value = hermes_parser->current_token->value;

            if (strcmp(token_value, STATEMENT_WHILE) == 0)
                return hermes_parser_parse_while(hermes_parser, scope);

            if (strcmp(token_value, STATEMENT_IF) == 0)
                return hermes_parser_parse_if(hermes_parser, scope);

            if (strcmp(token_value, VALUE_FALSE) == 0 || strcmp(token_value, VALUE_TRUE) == 0)
                return hermes_parser_parse_boolean(hermes_parser, scope);

            if (strcmp(token_value, STATEMENT_RETURN) == 0)
                return hermes_parser_parse_return(hermes_parser, scope);

            if (
                strcmp(token_value, DATA_TYPE_VOID) == 0 ||
                strcmp(token_value, DATA_TYPE_INT) == 0 ||
                strcmp(token_value, DATA_TYPE_STRING) == 0 ||
                strcmp(token_value, DATA_TYPE_FLOAT) == 0 ||
                strcmp(token_value, DATA_TYPE_BOOLEAN) == 0 ||
                strcmp(token_value, DATA_TYPE_OBJECT) == 0
            )
                return hermes_parser_parse_function_definition(hermes_parser, scope);

            hermes_parser_eat(hermes_parser, TOKEN_ID);

            switch (hermes_parser->current_token->type)
            {
                case TOKEN_LPAREN: return hermes_parser_parse_function_call(hermes_parser, scope); break;
                case TOKEN_EQUALS: return hermes_parser_parse_variable_assignment(hermes_parser, scope); break;
                default: return hermes_parser_parse_variable(hermes_parser, scope); break;
            }
        } break;
        case TOKEN_NUMBER_VALUE: case TOKEN_STRING_VALUE: return hermes_parser_parse_expr(hermes_parser, scope); break;
        default: return init_ast(AST_NOOP); break;
    }
}

AST_T* hermes_parser_parse_statements(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* compound = init_ast(AST_COMPOUND);

    compound->compound_value = init_dynamic_list(sizeof(struct AST_STRUCT));

    dynamic_list_append(compound->compound_value, hermes_parser_parse_statement(hermes_parser, scope));

    while (hermes_parser->current_token->type == TOKEN_SEMI)
    {

        hermes_parser_eat(hermes_parser, TOKEN_SEMI);
        dynamic_list_append(compound->compound_value, hermes_parser_parse_statement(hermes_parser, scope));
    }

    return compound;
}

AST_T* hermes_parser_parse_type(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_type = init_ast(AST_TYPE);
    ast_type->type_value = hermes_parser->current_token->value;

    hermes_parser_eat(hermes_parser, TOKEN_ID);

    return ast_type;
}

// values

AST_T* hermes_parser_parse_float(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_float = init_ast(AST_FLOAT);
    ast_float->float_value = (float) atof(hermes_parser->current_token->value);

    hermes_parser_eat(hermes_parser, TOKEN_NUMBER_VALUE);

    return ast_float;
}

AST_T* hermes_parser_parse_string(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_string = init_ast(AST_STRING);
    ast_string->string_value = hermes_parser->current_token->value;

    hermes_parser_eat(hermes_parser, TOKEN_STRING_VALUE);

    return ast_string;
}

AST_T* hermes_parser_parse_integer(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_integer = init_ast(AST_INTEGER);
    ast_integer->int_value = atoi(hermes_parser->current_token->value);

    hermes_parser_eat(hermes_parser, TOKEN_NUMBER_VALUE);

    return ast_integer;
}

AST_T* hermes_parser_parse_array(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
}

AST_T* hermes_parser_parse_boolean(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_boolean = init_ast(AST_BOOLEAN);
    
    if (strcmp(hermes_parser->current_token->value, "false") == 0)
        ast_boolean->boolean_value = 0; 
    else if (strcmp(hermes_parser->current_token->value, "true") == 0)
        ast_boolean->boolean_value = 1;
    else
        printf("%s is not a boolean value\n");

    hermes_parser_eat(hermes_parser, TOKEN_ID);

    return ast_boolean;
}

AST_T* hermes_parser_parse_variable(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = hermes_parser->prev_token->value;

    return ast_variable;
}


AST_T* hermes_parser_parse_variable_assignment(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    char* variable_name = hermes_parser->prev_token->value;
    hermes_parser_eat(hermes_parser, TOKEN_EQUALS);
    AST_T* ast_variable_assignment = init_ast(AST_VARIABLE_ASSIGNMENT);
    ast_variable_assignment->variable_name = variable_name;
    ast_variable_assignment->variable_value = hermes_parser_parse_expr(hermes_parser, scope);

    return ast_variable_assignment;
}

AST_T* hermes_parser_parse_object(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_object = init_ast(AST_OBJECT);
    ast_object->object_children = init_dynamic_list(sizeof(struct AST_STRUCT));

    hermes_parser_eat(hermes_parser, TOKEN_LBRACE);

    if (hermes_parser->current_token->type != TOKEN_RBRACE)
    {
        if (hermes_parser->current_token->type == TOKEN_ID)
            dynamic_list_append(ast_object->object_children, hermes_parser_parse_function_definition(hermes_parser, scope));

        while (hermes_parser->current_token->type == TOKEN_SEMI)
        {
            hermes_parser_eat(hermes_parser, TOKEN_SEMI);

            if (hermes_parser->current_token->type == TOKEN_ID)
                dynamic_list_append(ast_object->object_children, hermes_parser_parse_function_definition(hermes_parser, scope));
        }
    }
    
    hermes_parser_eat(hermes_parser, TOKEN_RBRACE);

    return ast_object;
}

// math

AST_T* hermes_parser_parse_factor(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{ 
    if (hermes_parser->current_token->type == TOKEN_ID)
    {
        hermes_parser_eat(hermes_parser, TOKEN_ID);

        switch (hermes_parser->current_token->type)
        {
            case TOKEN_LPAREN: return hermes_parser_parse_function_call(hermes_parser, scope); break;
            default: return hermes_parser_parse_variable(hermes_parser, scope); break;
        }
    }
    
    switch (hermes_parser->current_token->type)
    {
        case TOKEN_NUMBER_VALUE: return hermes_parser_parse_integer(hermes_parser, scope); break;
        case TOKEN_INTEGER_VALUE: return hermes_parser_parse_integer(hermes_parser, scope); break;
        case TOKEN_FLOAT_VALUE: return hermes_parser_parse_integer(hermes_parser, scope); break;
        case TOKEN_STRING_VALUE: return hermes_parser_parse_string(hermes_parser, scope); break;
        case TOKEN_LBRACE: return hermes_parser_parse_object(hermes_parser, scope); break;
        default: return hermes_parser_parse_expr(hermes_parser, scope); break;
    }
}

AST_T* hermes_parser_parse_term(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    char* token_value = hermes_parser->current_token->value;

    if (
        strcmp(token_value, DATA_TYPE_VOID) == 0 ||
        strcmp(token_value, DATA_TYPE_INT) == 0 ||
        strcmp(token_value, DATA_TYPE_STRING) == 0 ||
        strcmp(token_value, DATA_TYPE_FLOAT) == 0 ||
        strcmp(token_value, DATA_TYPE_BOOLEAN) == 0 ||
        strcmp(token_value, DATA_TYPE_OBJECT) == 0
    ) // this is to be able to have variable definitions inside of function definition parantheses.
        return hermes_parser_parse_function_definition(hermes_parser, scope);

    AST_T* node = hermes_parser_parse_factor(hermes_parser, scope);
    AST_T* ast_binop = (void*) 0;

    while (
        hermes_parser->current_token->type == TOKEN_DIV ||        
        hermes_parser->current_token->type == TOKEN_STAR 
    )
    {
        int binop_operator = hermes_parser->current_token->type;
        hermes_parser_eat(hermes_parser, hermes_parser->current_token->type);
        
        ast_binop = init_ast(AST_BINOP);
        
        ast_binop->binop_left = node;
        ast_binop->binop_operator = binop_operator;
        ast_binop->binop_right = hermes_parser_parse_factor(hermes_parser, scope);

        node = ast_binop;
    }
    
    return node;
}

AST_T* hermes_parser_parse_expr(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* node = hermes_parser_parse_term(hermes_parser, scope);
    AST_T* ast_binop = (void*) 0;

    while (
        hermes_parser->current_token->type == TOKEN_PLUS ||
        hermes_parser->current_token->type == TOKEN_MINUS ||
        hermes_parser->current_token->type == TOKEN_EQUALS
    )
    {
        int binop_operator = hermes_parser->current_token->type;
        hermes_parser_eat(hermes_parser, hermes_parser->current_token->type);

        ast_binop = init_ast(AST_BINOP);

        ast_binop->binop_left = node;
        ast_binop->binop_operator = binop_operator;
        ast_binop->binop_right = hermes_parser_parse_term(hermes_parser, scope);

        node = ast_binop;
    }

    return node;
}

// statements

AST_T* hermes_parser_parse_break(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    return init_ast(AST_BREAK);
}

AST_T* hermes_parser_parse_return(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    hermes_parser_eat(hermes_parser, TOKEN_ID);
    AST_T* ast_return = init_ast(AST_RETURN);

    if (hermes_parser->current_token->type != TOKEN_SEMI)
        ast_return->return_value = hermes_parser_parse_expr(hermes_parser, scope);

    return ast_return;
}

AST_T* hermes_parser_parse_if(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_if = init_ast(AST_IF);
    
    if (hermes_parser->current_token->type == TOKEN_ID) {
        hermes_parser_eat(hermes_parser, TOKEN_ID);
    }
    
    if (hermes_parser->current_token->type == TOKEN_LPAREN)
    {
        hermes_parser_eat(hermes_parser, TOKEN_LPAREN);
        ast_if->if_expr = hermes_parser_parse_expr(hermes_parser, scope);
        hermes_parser_eat(hermes_parser, TOKEN_RPAREN);
    }

    hermes_parser_eat(hermes_parser, TOKEN_LBRACE);
    ast_if->if_body = hermes_parser_parse_statements(hermes_parser, scope);
    hermes_parser_eat(hermes_parser, TOKEN_RBRACE);

    if (strcmp(hermes_parser->current_token->value, STATEMENT_ELSE) == 0)
    {
        hermes_parser_eat(hermes_parser, TOKEN_ID);
        ast_if->if_otherwise = hermes_parser_parse_if(hermes_parser, scope);
    }

    return ast_if;
}

// loops

AST_T* hermes_parser_parse_while(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    hermes_parser_eat(hermes_parser, TOKEN_ID);
    hermes_parser_eat(hermes_parser, TOKEN_LPAREN);
    AST_T* ast_while = init_ast(AST_WHILE);
    ast_while->while_expr = hermes_parser_parse_expr(hermes_parser, scope);
    hermes_parser_eat(hermes_parser, TOKEN_RPAREN);
    hermes_parser_eat(hermes_parser, TOKEN_LBRACE);
    ast_while->while_body = hermes_parser_parse_statements(hermes_parser, scope);
    hermes_parser_eat(hermes_parser, TOKEN_RBRACE);

    return ast_while;
}

// functions

AST_T* hermes_parser_parse_function_call(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_function_call = init_ast(AST_FUNCTION_CALL);
    ast_function_call->function_call_name = hermes_parser->prev_token->value;
    hermes_parser_eat(hermes_parser, TOKEN_LPAREN);
    ast_function_call->function_call_arguments = init_dynamic_list(sizeof(struct AST_STRUCT));

    if (hermes_parser->current_token->type != TOKEN_RPAREN)
    {
        dynamic_list_append(ast_function_call->function_call_arguments, hermes_parser_parse_expr(hermes_parser, scope));

        while (hermes_parser->current_token->type == TOKEN_COMMA)
        {
            hermes_parser_eat(hermes_parser, TOKEN_COMMA);
            dynamic_list_append(ast_function_call->function_call_arguments, hermes_parser_parse_expr(hermes_parser, scope));
        }
    }

    hermes_parser_eat(hermes_parser, TOKEN_RPAREN);

    return ast_function_call;
}

AST_T* hermes_parser_parse_function_definition(hermes_parser_T* hermes_parser, hermes_scope_T* scope)
{
    AST_T* ast_type = hermes_parser_parse_type(hermes_parser, scope);
    char* function_name = hermes_parser->current_token->value;
    hermes_parser_eat(hermes_parser, TOKEN_ID);

    if (hermes_parser->current_token->type == TOKEN_LPAREN)
    {
        // alright, it sure is a function definition!
        
        AST_T* ast_function_definition = init_ast(AST_FUNCTION_DEFINITION);
        ast_function_definition->function_name = function_name;
        ast_function_definition->function_definition_type = ast_type;
        ast_function_definition->function_definition_arguments = init_dynamic_list(sizeof(struct AST_STRUCT));

        hermes_parser_eat(hermes_parser, TOKEN_LPAREN);

        if (hermes_parser->current_token->type != TOKEN_RPAREN)
        {
            dynamic_list_append(ast_function_definition->function_definition_arguments, hermes_parser_parse_expr(hermes_parser, scope));

            while (hermes_parser->current_token->type == TOKEN_COMMA)
            {
                hermes_parser_eat(hermes_parser, TOKEN_COMMA);
                dynamic_list_append(ast_function_definition->function_definition_arguments, hermes_parser_parse_expr(hermes_parser, scope));
            }
        }

        hermes_parser_eat(hermes_parser, TOKEN_RPAREN);

        hermes_parser_eat(hermes_parser, TOKEN_LBRACE);
        ast_function_definition->function_definition_body = hermes_parser_parse_statements(hermes_parser, scope);
        hermes_parser_eat(hermes_parser, TOKEN_RBRACE);

        return ast_function_definition;
    }
    else
    {
        // alright, it is a variable definition.
        AST_T* ast_variable_definition = init_ast(AST_VARIABLE_DEFINITION);
        ast_variable_definition->variable_name = function_name;
        ast_variable_definition->variable_type = ast_type;
        
        if (hermes_parser->current_token->type == TOKEN_EQUALS)
        {
            hermes_parser_eat(hermes_parser, TOKEN_EQUALS);
            ast_variable_definition->variable_value = hermes_parser_parse_expr(hermes_parser, scope);
        }

        return ast_variable_definition;
    }
}
