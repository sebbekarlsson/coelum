#include <coelum/main.h>
#include <coelum/io.h>
#include <coelum/hermes/lexer.h>
#include <coelum/hermes/hermes_parser.h>
#include <coelum/hermes/hermes_runtime.h>
#include <coelum/scene.h>
#include <coelum/theatre.h>
#include "include/scene_impl.h"
#include <stdio.h>
#include <string.h>


extern theatre_T* THEATRE;

int main(int argc, char* argv[])
{ 
    coelum_init();

    // time to load some configs
    
    lexer_T* lexer = init_lexer(read_file("scenes.txt"));
    hermes_parser_T* parser = init_hermes_parser(lexer);
    AST_T* scenes_node = hermes_parser_parse(parser, (void*) 0);
    runtime_T* runtime = init_runtime();
    runtime_visit(runtime, scenes_node);

    hermes_scope_T* runtime_scope = get_scope(runtime, scenes_node);

    for (int i = 0; i < runtime_scope->variable_definitions->size; i++)
    {
        AST_T* ast_vardef = (AST_T*) runtime_scope->variable_definitions->items[i];

        char* scene_name = ast_vardef->variable_name;

        printf("scene %s\n", scene_name);

        // what we are looking for
        float r;
        float g;
        float b;

        AST_T* object_node = ast_vardef->variable_value;
        hermes_scope_T* scene_scope = get_scope(runtime, object_node);
        AST_T* ast_actors_list;

        // trying to collect values from each scene block
        for (int j = 0; j < scene_scope->variable_definitions->size; j++)
        {
            AST_T* scene_vardef = (AST_T*) scene_scope->variable_definitions->items[j];

            printf("EEEEE%s %d\n", scene_vardef->variable_name, scene_vardef->variable_value->int_value);

            if (strcmp(scene_vardef->variable_name, "r") == 0)
                r = scene_vardef->variable_value->int_value;
            if (strcmp(scene_vardef->variable_name, "g") == 0)
                g = scene_vardef->variable_value->int_value;
            if (strcmp(scene_vardef->variable_name, "b") == 0)
                b = scene_vardef->variable_value->int_value;
            if (strcmp(scene_vardef->variable_name, "actors") == 0)
                ast_actors_list = scene_vardef->variable_value;
        }

        // building a scene

        scene_impl_T* scene_impl = init_scene_impl();
        scene_T* scene = (scene_T*) scene_impl;
        scene->bg_r = r;
        scene->bg_g = g;
        scene->bg_b = b;

        // register the built scene

        scene_manager_register_scene(THEATRE->scene_manager, (scene_T*) scene);

        for (int ii = 0; ii < ast_actors_list->list_children->size; ii++)
        {
            float ax;
            float ay;
            float az;
            char* type_name;

            AST_T* ast_actor_object = ast_actors_list->list_children->items[ii];

            for (int ij = 0; ij < ast_actor_object->object_children->size; ij++)
            {
                AST_T* ast_actor_vardef = (AST_T*) ast_actor_object->object_children->items[ij];

                if (strcmp(ast_actor_vardef->variable_name, "type_name") == 0)
                    type_name = ast_actor_vardef->variable_value->string_value;
                if (strcmp(ast_actor_vardef->variable_name, "x") == 0)
                    ax = ast_actor_vardef->variable_value->int_value;
                if (strcmp(ast_actor_vardef->variable_name, "y") == 0)
                    ay = ast_actor_vardef->variable_value->int_value;
                if (strcmp(ast_actor_vardef->variable_name, "z") == 0)
                    az = ast_actor_vardef->variable_value->int_value;
            
            }

            printf("%s (%0.6f, %0.6f, %0.6f)\n", type_name, ax, ay, az);
            actor_abstract_T* actor_abstract = init_actor_abstract(type_name, ax, ay, az);
            dynamic_list_append(scene_impl->on_load_actors, actor_abstract);
        }
    }
    printf("All scenes initialized\n");

    if (coelum_main(argc, argv))
    {
        printf("Coelum crashed.");
    }

    return 0;
}
