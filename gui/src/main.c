#include <coelum/main.h>
#include "include/scene_main.h"
#include "include/colors.h"
#include <coelum/theatre.h>

// lexing stuff
/*#include <coelum/io.h>
#include "parsing/include/lexer.h"
#include "parsing/include/config_parser.h"*/


extern theatre_T* THEATRE;

int main(int argc, char* argv[])
{

    /*lexer_T* lexer = init_lexer(read_file("test.txt"));
    config_parser_T* parser = init_config_parser(lexer);
    config_parser_parse(parser);
    //lexer_dump(lexer);
    return 0;*/
    coelum_init();

    scene_manager_register_scene(THEATRE->scene_manager, (scene_T*) init_scene_main());

    if (coelum_main(argc, argv))
    {
        printf("Coelum crashed.");
    }

    return 0;
}
