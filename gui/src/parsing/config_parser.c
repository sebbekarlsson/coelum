#include "include/config_parser.h"


config_parser_T* init_config_parser(lexer_T* lexer)
{
    config_parser_T* parser = calloc(1, sizeof(struct CONFIG_PARSER_STRUCT));
    parser->lexer = lexer;
    parser->blocks = init_dynamic_list(sizeof(struct AST_STRUCT));
    parser->current_token = lexer_get_next_token(lexer);
}

void config_parser_eat(config_parser_T* parser, int token_type)
{
    if (parser->current_token->type != token_type)
    {
        printf("Unexpected token `%s`.\n", parser->current_token->value);
        exit(1);
    }
    else if (parser->current_token->type == token_type)
    {
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
}

AST_T* config_parser_parse(config_parser_T* parser)
{
    if (parser->current_token->type == TOKEN_ID)
        config_parser_parse_block(parser);

    while (parser->current_token->type == TOKEN_SEMI)
    {
        config_parser_eat(parser, TOKEN_SEMI);

        if (parser->current_token->type == TOKEN_ID)
            config_parser_parse_block(parser);
    }
}

AST_T* config_parser_parse_block(config_parser_T* parser)
{
    char* name = parser->current_token->value;

    config_parser_eat(parser, TOKEN_ID);
    config_parser_eat(parser, TOKEN_LBRACE);

    AST_T* block = init_ast("block");
    ast_set_key_value(block, "name", name);

    dynamic_list_T* definitions = init_dynamic_list(sizeof(struct AST_STRUCT));

    if (parser->current_token->type == TOKEN_ID)
        dynamic_list_append(definitions, config_parser_parse_variable_definition(parser));

    while (parser->current_token->type == TOKEN_SEMI)
    {
        config_parser_eat(parser, TOKEN_SEMI);

        if (parser->current_token->type == TOKEN_ID)
            dynamic_list_append(definitions, config_parser_parse_variable_definition(parser));
    }

    ast_set_key_value(block, "variable_definitions", definitions);
    config_parser_eat(parser, TOKEN_RBRACE);

    dynamic_list_append(parser->blocks, block);

    return block;
}

AST_T* config_parser_parse_variable_definition(config_parser_T* parser)
{
    char* key = parser->current_token->value;
    config_parser_eat(parser, TOKEN_ID);
    config_parser_eat(parser, TOKEN_EQUALS);
    char* value = parser->current_token->value;

    if (parser->current_token->type == TOKEN_NUMBER_VALUE)
        config_parser_eat(parser, TOKEN_NUMBER_VALUE);
    else
    if (parser->current_token->type == TOKEN_STRING_VALUE)
        config_parser_eat(parser, TOKEN_STRING_VALUE);

    AST_T* variable_definition = init_ast("variable_definition");
    ast_set_key_value(variable_definition, "key", key);
    ast_set_key_value(variable_definition, "value", value);

    return variable_definition;
}
