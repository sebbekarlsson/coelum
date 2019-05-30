/*#include "include/config_parser.h"
#include <string.h>


config_parser_T* init_config_parser(lexer_T* lexer)
{
    config_parser_T* parser = calloc(1, sizeof(struct CONFIG_PARSER_STRUCT));
    parser->lexer = lexer;
    parser->blocks = init_dynamic_list(sizeof(struct AST_STRUCT));
    parser->current_token = lexer_get_next_token(lexer);

    return parser;
}

void config_parser_eat(config_parser_T* parser, int token_type)
{
    if (parser->current_token->type != token_type)
    {
        printf("Unexpected token `%s`, was expecting `%d`.\n", parser->current_token->value, token_type);
        exit(1);
    }
    else if (parser->current_token->type == token_type)
    {
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
}

AST_T* config_parser_parse(config_parser_T* parser)
{
    switch (parser->current_token->type)
    {
        case TOKEN_LBRACKET: return config_parser_parse_list(parser); break;
        case TOKEN_LBRACE: return config_parser_parse_block(parser); break;
    }
}

AST_T* config_parser_parse_block(config_parser_T* parser)
{
    config_parser_eat(parser, TOKEN_LBRACE);

    AST_T* block = init_ast("block");

    dynamic_list_T* definitions = init_dynamic_list(sizeof(struct AST_STRUCT));

    if (parser->current_token->type == TOKEN_ID)
        dynamic_list_append(definitions, config_parser_parse_variable_definition(parser));

    while (parser->current_token->type == TOKEN_SEMI)
    {
        config_parser_eat(parser, TOKEN_SEMI);

        if (parser->current_token->type == TOKEN_ID)
            dynamic_list_append(definitions, config_parser_parse_variable_definition(parser));
    }

    ast_set_key_value(block, "definitions", definitions);
    config_parser_eat(parser, TOKEN_RBRACE);

    return block;
}

AST_T* config_parser_parse_variable_definition(config_parser_T* parser)
{
    char* key = parser->current_token->value;
    config_parser_eat(parser, TOKEN_ID);
    config_parser_eat(parser, TOKEN_EQUALS);
    void* value = (void*) 0;

    if (parser->current_token->type == TOKEN_NUMBER_VALUE)
    {
        value = parser->current_token->value;
        config_parser_eat(parser, TOKEN_NUMBER_VALUE);
    }
    else
    if (parser->current_token->type == TOKEN_STRING_VALUE)
    {
        value = parser->current_token->value;
        config_parser_eat(parser, TOKEN_STRING_VALUE);
    }
    else
    if (parser->current_token->type == TOKEN_LBRACE)
    {
        value = config_parser_parse_block(parser);
        AST_T* ast_value = (AST_T*) value;
        ast_set_key_value(ast_value, "name", key);
        dynamic_list_append(parser->blocks, ast_value);
    }
    else
    if (parser->current_token->type == TOKEN_LBRACKET)
    {
        value = config_parser_parse_list(parser);
    }

    AST_T* variable_definition = init_ast("variable_definition");

    ast_set_key_value(variable_definition, "key", key);
    ast_set_key_value(variable_definition, "value", value);

    return variable_definition;
}

AST_T* config_parser_parse_list(config_parser_T* parser)
{
    config_parser_eat(parser, TOKEN_LBRACKET);

    AST_T* ast_list = init_ast("list");

    dynamic_list_T* items = init_dynamic_list(sizeof(struct AST_STRUCT));

    dynamic_list_append(items, config_parser_parse(parser));

    while (parser->current_token->type == TOKEN_COMMA)
    {
        config_parser_eat(parser, TOKEN_COMMA);
        dynamic_list_append(items, config_parser_parse(parser));
    }

    config_parser_eat(parser, TOKEN_RBRACKET);

    ast_set_key_value(ast_list, "items", items);

    return ast_list;
}

dynamic_list_T* config_parser_get_keys(AST_T* node)
{
    dynamic_list_T* keys = init_dynamic_list(sizeof(char*));

    if (strcmp(node->type_name, "block") == 0)
    {
        dynamic_list_T* definitions = ast_get_value_by_key(node, "definitions");

        for (int i = 0; i < definitions->size; i++)
        {
            AST_T* ast = (AST_T*) definitions->items[i];

            dynamic_list_append(keys, ast_get_value_by_key(ast, "key"));
        }
    }

    return keys;
}

void* config_parser_get_by_key(AST_T* node, char* key)
{
    if (strcmp(node->type_name, "block") == 0)
    {
        dynamic_list_T* definitions = ast_get_value_by_key(node, "definitions");

        for (int i = 0; i < definitions->size; i++)
        {
            AST_T* ast = (AST_T*) definitions->items[i];

            if (strcmp(ast_get_value_by_key(ast, "key"), key) == 0)
                return ast_get_value_by_key(ast, "value");
        }
    }

    return (void*) 0;
}*/
