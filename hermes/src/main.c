#include "include/main.h"
#include "include/lexer.h"
#include "include/hermes_parser.h"
#include "include/hermes_runtime.h"
#include <coelum/io.h>


int main(int argc, char* argv[])
{
    lexer_T* lexer = init_lexer(read_file(argv[1]));
    
    hermes_parser_T* parser = init_hermes_parser(lexer);
    AST_T* node = hermes_parser_parse(parser, (void*) 0);
    runtime_T* runtime = init_runtime();
    runtime_visit(runtime, node);
}
