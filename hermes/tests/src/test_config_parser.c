/*#include "include/main.h"
#include "../../src/include/config_parser.h"
#include <string.h>


void test_config_parser(void** state)
{
    lexer_T* lexer = init_lexer(
        "{"
           " tomato = {"
           "     width = 16;"
           "     height = 16;"
           "     texture = \"res/img/tomato.png\";"
           "     tick = \"scripts/tomato.zcs\";"
           " };"
           " banana = {"
           "     width = 32;"
           "     height = 32;"
           "     texture = \"res/img/banana.png\";"
           "     tick = \"scripts/banana.zcs\";"
           " };"
        "};"
    );
    
    config_parser_T* parser = init_config_parser(lexer);
    AST_T* node = config_parser_parse(parser);
    dynamic_list_T* keys = config_parser_get_keys(node);

    char* key_0 = (char*) keys->items[0];
    assert_true(strcmp(key_0, "tomato") == 0);

    char* key_1 = (char*) keys->items[1];
    assert_true(strcmp(key_1, "banana") == 0);

    for (int i = 0; i < keys->size; i++)
    {
        AST_T* ast = config_parser_get_by_key(node, (char*) keys->items[i]);

        if (strcmp((char*) keys->items[i], "tomato") == 0)
        {
            assert_true(strcmp(config_parser_get_by_key(ast, "width"), "16") == 0);
            assert_true(strcmp(config_parser_get_by_key(ast, "height"), "16") == 0);
            assert_true(strcmp(config_parser_get_by_key(ast, "texture"), "res/img/tomato.png") == 0);
            assert_true(strcmp(config_parser_get_by_key(ast, "tick"), "scripts/tomato.zcs") == 0);
        }
        else
        if (strcmp((char*) keys->items[i], "banana") == 0)
        {
            assert_true(strcmp(config_parser_get_by_key(ast, "width"), "32") == 0);
            assert_true(strcmp(config_parser_get_by_key(ast, "height"), "32") == 0);
            assert_true(strcmp(config_parser_get_by_key(ast, "texture"), "res/img/banana.png") == 0);
            assert_true(strcmp(config_parser_get_by_key(ast, "tick"), "scripts/banana.zcs") == 0);
        }
    }
    
    assert_true(parser != NULL);
}*/
