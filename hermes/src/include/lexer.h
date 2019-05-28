#ifndef HERMES_LEXER_H
#define HERMES_LEXER_H
/**
 * This is a general purpose lexer.
 */
#include "token.h"


typedef struct LEXER_STRUCT
{
    char* contents;
    char current_char;
    unsigned int char_index;
} lexer_T;

lexer_T* init_lexer(char* contents);

token_T* lexer_get_next_token(lexer_T* lexer);

token_T* lexer_advance_with_token(lexer_T* lexer, int type);

void lexer_advance(lexer_T* lexer);

void lexer_expect_char(lexer_T* lexer, char c);

void lexer_skip_whitespace(lexer_T* lexer);

token_T* lexer_collect_string(lexer_T* lexer);

token_T* lexer_collect_number(lexer_T* lexer);

token_T* lexer_collect_id(lexer_T* lexer);

void lexer_dump(lexer_T* lexer);

void lexer_free(lexer_T* lexer);
#endif
