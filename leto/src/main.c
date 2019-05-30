#include <coelum/main.h>
#include <coelum/io.h>
#include <coelum/hermes/lexer.h>
#include <coelum/hermes/config_parser.h>
#include <coelum/scene.h>
#include <coelum/theatre.h>
#include "include/scene_impl.h"
#include <stdio.h>


extern theatre_T* THEATRE;

int main(int argc, char* argv[])
{ 
    coelum_init();

    // time to load some configs
    
    lexer_T* lexer = init_lexer(read_file("scenes.txt"));
    config_parser_T* parser = init_config_parser(lexer);
    AST_T* scenes_node = config_parser_parse(parser);
    
    dynamic_list_T* scene_names = config_parser_get_keys(scenes_node);

    lexer_free(lexer);
    free(parser); 

    for (int i = 0; i < scene_names->size; i++)
    {
        char* scene_name = (char*) scene_names->items[i];

        // what we are looking for
        float r;
        float g;
        float b;

        AST_T* scene_block = (AST_T*) config_parser_get_by_key(scenes_node, scene_name);

        // trying to collect values from each scene block

        r = atof((char*) config_parser_get_by_key(scene_block, "r"));
        g = atof((char*) config_parser_get_by_key(scene_block, "r"));
        b = atof((char*) config_parser_get_by_key(scene_block, "r"));

        // building a scene

        scene_impl_T* scene_impl = init_scene_impl();
        scene_T* scene = (scene_T*) scene_impl;
        scene->bg_r = r;
        scene->bg_g = g;
        scene->bg_b = b;

        // register the built scene

        scene_manager_register_scene(THEATRE->scene_manager, (scene_T*) scene);

        AST_T* actors_block = (AST_T*) config_parser_get_by_key(scene_block, "actors");

        dynamic_list_T* actors = (dynamic_list_T*) ast_get_value_by_key(actors_block, "items");

        for (int ii = 0; ii < actors->size; ii++)
        {
            float ax;
            float ay;
            float az;
            char* type_name;

            AST_T* actor_block = (AST_T*) actors->items[ii];

            type_name = (char*) config_parser_get_by_key(actor_block, "type_name");
            ax = atof((char*) config_parser_get_by_key(actor_block, "x"));
            ay = atof((char*) config_parser_get_by_key(actor_block, "y"));
            az = atof((char*) config_parser_get_by_key(actor_block, "z"));

            printf("%s (%0.6f, %0.6f, %0.6f)\n", type_name, ax, ay, az);
            actor_abstract_T* actor_abstract = init_actor_abstract(type_name, ax, ay, az);
            dynamic_list_append(scene_impl->on_load_actors, actor_abstract);
        }
    }

    if (coelum_main(argc, argv))
    {
        printf("Coelum crashed.");
    }

    return 0;
}
