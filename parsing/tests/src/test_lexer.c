#include "include/main.h"
#include "include/test_lexer.h"
#include "../../src/include/lexer.h"


void test_lexer_behavior(void** state)
{
    lexer_T* lexer = init_lexer(
        "{ actor = { width = 32; height = 32; texture = \"/tmp\"; }; }"
    );

    assert_true(lexer != NULL);
    
    assert_true(lexer->current_char == '{');

    assert_true(lexer_get_next_token(lexer)->type == TOKEN_LBRACE);

    assert_true(lexer_get_next_token(lexer)->type == TOKEN_ID);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_EQUALS);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_LBRACE);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_ID);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_EQUALS);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_NUMBER_VALUE);

    assert_true(lexer->current_char == ';');

    assert_true(lexer_get_next_token(lexer)->type == TOKEN_SEMI);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_ID);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_EQUALS);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_NUMBER_VALUE);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_SEMI);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_ID);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_EQUALS);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_STRING_VALUE);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_SEMI);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_RBRACE);
    assert_true(lexer_get_next_token(lexer)->type == TOKEN_SEMI);

    assert_true(lexer_get_next_token(lexer)->type == TOKEN_RBRACE);

    assert_true(lexer->current_char == '}');
}
