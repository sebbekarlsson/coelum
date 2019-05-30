#ifndef HERMES_PARSER_H
#define HERMES_PARSER_H
#include "lexer.h"
#include "AST.h"
#include "token.h"


typedef struct HERMES_PARSER_STRUCT
{
    lexer_T* lexer;
    token_T* prev_token;
    token_T* current_token;
} hermes_parser_T;

hermes_parser_T* init_hermes_parser(lexer_T* lexer);

// etc

AST_T* hermes_parser_parse(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_eat(hermes_parser_T* hermes_parser, int token_type);

AST_T* hermes_parser_parse_statement(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_statements(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_type(hermes_parser_T* hermes_parser);

// values

AST_T* hermes_parser_parse_float(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_string(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_integer(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_array(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_boolean(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_variable(hermes_parser_T* hermes_parser);

// math

AST_T* hermes_parser_parse_factor(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_term(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_expr(hermes_parser_T* hermes_parser);

// statements

AST_T* hermes_parser_parse_break(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_return(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_if(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_else(hermes_parser_T* hermes_parser);

// loops

AST_T* hermes_parser_parse_while(hermes_parser_T* hermes_parser);

// functions

AST_T* hermes_parser_parse_function_call(hermes_parser_T* hermes_parser);

AST_T* hermes_parser_parse_function_definition(hermes_parser_T* hermes_parser);
#endif
