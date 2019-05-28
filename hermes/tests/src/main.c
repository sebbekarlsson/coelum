#include "include/main.h"
#include "include/test_lexer.h"
#include "include/test_config_parser.h"


int main(int argc, char* argv[])
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test(test_lexer_behavior),
        cmocka_unit_test(test_config_parser),
    };

    int count_fail_tests =
        cmocka_run_group_tests (tests, NULL, NULL);

    return count_fail_tests;
}
