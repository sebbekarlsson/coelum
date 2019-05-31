#include "include/main.h"
#include "../../src/include/hermes_parser.h"
#include "../../src/include/hermes_runtime.h"
#include <string.h>


void test_hermes_runtime_does_not_crash(void** state)
{
    lexer_T* lexer = init_lexer(
        "string getName() { string x = \"John\"; return x; }; print(getName());"
    );
    
    hermes_parser_T* parser = init_hermes_parser(lexer);
    AST_T* node = hermes_parser_parse(parser, (void*) 0);
    runtime_T* runtime = init_runtime();
    runtime_visit(runtime, node);

    assert_true(runtime != NULL);
}
