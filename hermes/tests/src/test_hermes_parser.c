#include "include/main.h"
#include "../../src/include/hermes_parser.h"
#include <string.h>


void test_hermes_parser_variable_definition_does_not_crash(void** state)
{
    lexer_T* lexer = init_lexer(
        "int x;\nint y = 2;"
    );
    
    hermes_parser_T* parser = init_hermes_parser(lexer);
    AST_T* node = hermes_parser_parse(parser, (void*) 0);
    assert_true(parser != NULL);
}

void test_hermes_parser_function_definition_does_not_crash(void** state)
{
    lexer_T* lexer = init_lexer(
        "void dosomething(int x) { print(\"hello\"); };"
    );
    
    hermes_parser_T* parser = init_hermes_parser(lexer);
    AST_T* node = hermes_parser_parse(parser, (void*) 0);
    assert_true(parser != NULL);
}
