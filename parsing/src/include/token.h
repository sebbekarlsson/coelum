#ifndef COELUMG_TOKEN_H
#define COELUMG_TOKEN_H
typedef struct TOKEN_STRUCT
{
    enum
    {
        TOKEN_STRING_VALUE,
        TOKEN_NUMBER_VALUE,
        TOKEN_ID,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_LBRACKET,
        TOKEN_RBRACKET,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_EQUALS,
        TOKEN_SEMI,
        TOKEN_COMMA,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_STAR,
        TOKEN_DIV,
        TOKEN_PERCENTAGE,
        TOKEN_DOT,
        TOKEN_EOF,
    } type;

    char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif
