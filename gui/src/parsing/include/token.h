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
        TOKEN_EQUALS,
        TOKEN_SEMI,
        TOKEN_EOF,
    } type;

    char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif
