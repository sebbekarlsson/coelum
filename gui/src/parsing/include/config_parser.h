#ifndef COELUMG_CONFIG_PARSER_H
#define COELUMG_CONFIG_PARSER_H
#include "lexer.h"
#include "AST.h"
#include "token.h"
#include <coelum/dynamic_list.h>


typedef struct CONFIG_PARSER_STRUCT
{
    lexer_T* lexer;
    token_T* current_token;
    dynamic_list_T* blocks;
} config_parser_T;

config_parser_T* init_config_parser(lexer_T* lexer);

void config_parser_eat(config_parser_T* parser, int token_type);

AST_T* config_parser_parse(config_parser_T* parser);

AST_T* config_parser_parse_block(config_parser_T* parser);

AST_T* config_parser_parse_variable_definition(config_parser_T* parser);
#endif
