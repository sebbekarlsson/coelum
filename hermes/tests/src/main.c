#include "include/main.h"
#include "include/test_lexer.h"
#include "include/test_hermes_parser.h"
#include "include/test_hermes_runtime.h"


int main(int argc, char* argv[])
{
    const struct CMUnitTest tests [] =
    {
        /*cmocka_unit_test(test_lexer_behavior),
        cmocka_unit_test(test_hermes_parser_variable_definition_does_not_crash),
        cmocka_unit_test(test_hermes_parser_function_definition_does_not_crash),*/
        cmocka_unit_test(test_hermes_runtime_does_not_crash),
    };

    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
