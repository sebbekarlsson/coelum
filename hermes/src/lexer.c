#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


char* char_to_string(char c)
{
    char* str = calloc(2, sizeof(char));
    str[0] = c;
    str[1] = '\0';

    return str;
}

lexer_T* init_lexer(char* contents)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->char_index = 0;
    lexer->current_char = lexer->contents[lexer->char_index];

    return lexer;
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
    while (lexer->current_char != '\0' && lexer->char_index < strlen(lexer->contents) - 1)
    {
        while (lexer->current_char == ' ' || (int) lexer->current_char == 10)
            lexer_skip_whitespace(lexer);

        if (isdigit(lexer->current_char))
            return lexer_collect_number(lexer);

        if (isalnum(lexer->current_char))
            return lexer_collect_id(lexer);

        switch(lexer->current_char)
        {
            case '"': return lexer_collect_string(lexer); break;
            case '{': return lexer_advance_with_token(lexer, TOKEN_LBRACE); break;
            case '}': return lexer_advance_with_token(lexer, TOKEN_RBRACE); break;
            case '[': return lexer_advance_with_token(lexer, TOKEN_LBRACKET); break;
            case ']': return lexer_advance_with_token(lexer, TOKEN_RBRACKET); break;
            case '(': return lexer_advance_with_token(lexer, TOKEN_LPAREN); break;
            case ')': return lexer_advance_with_token(lexer, TOKEN_RPAREN); break;
            case '=': return lexer_advance_with_token(lexer, TOKEN_EQUALS); break;
            case ';': return lexer_advance_with_token(lexer, TOKEN_SEMI); break;
            case ',': return lexer_advance_with_token(lexer, TOKEN_COMMA); break;
            case '+': return lexer_advance_with_token(lexer, TOKEN_PLUS); break;
            case '-': return lexer_advance_with_token(lexer, TOKEN_MINUS); break;
            case '*': return lexer_advance_with_token(lexer, TOKEN_STAR); break;
            case '/': return lexer_advance_with_token(lexer, TOKEN_DIV); break;
            case '%': return lexer_advance_with_token(lexer, TOKEN_PERCENTAGE); break;
            case '.': return lexer_advance_with_token(lexer, TOKEN_DOT); break;
            default: printf("unexpected %c\n", lexer->current_char); exit(1); break;
        }
    }

    init_token(TOKEN_EOF, "\0");
}

token_T* lexer_advance_with_token(lexer_T* lexer, int type)
{
    char* value = char_to_string(lexer->current_char);
    lexer_advance(lexer);
    return init_token(type, value);
}

void lexer_advance(lexer_T* lexer)
{
    if (lexer->current_char != '\0' && lexer->char_index < strlen(lexer->contents) - 1)
    {
        lexer->char_index += 1;
        lexer->current_char = lexer->contents[lexer->char_index];
    }
}

void lexer_expect_char(lexer_T* lexer, char c)
{
    if (lexer->current_char != c)
    {
        printf("Lexer expected the current char to be `%c`, but it was `%c`.", c, lexer->current_char);
        exit(1);
    }
}

void lexer_skip_whitespace(lexer_T* lexer)
{
    while (lexer->current_char == ' ' || (int) lexer->current_char == 10)
        lexer_advance(lexer);
}

token_T* lexer_collect_string(lexer_T* lexer)
{
    lexer_expect_char(lexer, '"');
    lexer_advance(lexer);
    char* buffer = calloc(1, sizeof(char));
    buffer[0] = '\0';

    while (lexer->current_char != '"')
    {
        char* strchar = char_to_string(lexer->current_char);
        buffer = realloc(buffer, strlen(buffer) + 2);
        strcat(buffer, strchar);
        free(strchar);

        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(TOKEN_STRING_VALUE, buffer);
}

token_T* lexer_collect_number(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));
    buffer[0] = '\0';

    while (isdigit(lexer->current_char))
    {
        char* strchar = char_to_string(lexer->current_char);
        buffer = realloc(buffer, strlen(buffer) + 2);
        strcat(buffer, strchar);
        free(strchar);

        lexer_advance(lexer);
    }

    return init_token(TOKEN_NUMBER_VALUE, buffer);
}

token_T* lexer_collect_id(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));
    buffer[0] = '\0';

    while (isalnum(lexer->current_char) || lexer->current_char == '_')
    {
        char* strchar = char_to_string(lexer->current_char);
        buffer = realloc(buffer, strlen(buffer) + 2);
        strcat(buffer, strchar);
        free(strchar);

        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, buffer);
}

void lexer_dump(lexer_T* lexer)
{
    token_T* token;

    while (1)
    {
        token = lexer_get_next_token(lexer);

        printf("TOKEN(%d, %s)\n", token->type, token->value);

        if (token->type == TOKEN_EOF)
            break;
    }
}

void lexer_free(lexer_T* lexer)
{
    free(lexer->contents);
    free(lexer);
}
