#include "include/config.h"
#include "include/io.h"
#include <hermes/hermes_parser.h>
#include <hermes/hermes_runtime.h>
#include <hermes/io.h>
#include <string.h>



config_T* init_config()
{
    config_T* config = calloc(1, sizeof(struct CONFIG_STRUCT));
    config->window_resizable = 0;

    return config;
}

void config_free(config_T* config)
{
    free(config);
}

void load_config_from_file_if_exists(config_T* config)
{
    if (!file_exists(CONFIG_FILENAME))
    {
        printf("Config file `%s` does not exist, using default config.\n", CONFIG_FILENAME);
        return;
    }

    hermes_lexer_T* hermes_lexer = init_hermes_lexer(read_file(CONFIG_FILENAME));
    hermes_parser_T* parser = init_hermes_parser(hermes_lexer);
    AST_T* root = hermes_parser_parse(parser, (void*) 0);
    runtime_T* runtime = init_runtime();
    runtime_visit(runtime, root);

    hermes_scope_T* runtime_scope = get_scope(runtime, root);

    for (int i = 0; i < runtime_scope->variable_definitions->size; i++)
    {
        AST_T* ast_vardef = (AST_T*) runtime_scope->variable_definitions->items[i];

        if (strcmp(ast_vardef->variable_name, "config") == 0)
        {
            AST_T* ast_obj = ast_vardef->variable_value;
            
            for (int j = 0; j < ast_obj->object_children->size; j++)
            {
                AST_T* ast_obj_var = (AST_T*) ast_obj->object_children->items[j];
                
                if (strcmp(ast_obj_var->variable_name, "window_resizable") == 0)
                {
                    config->window_resizable = ast_obj_var->variable_value->int_value;

                    break;
                }
            }
        }

        break;
    }

    hermes_lexer_free(hermes_lexer);
    ast_free(root);
}
