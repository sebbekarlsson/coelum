#include "include/config.h"
#include "include/io.h"
#include <string.h>
#include <json/json_parser.h>



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

    json_parser_T* parser = init_json_parser(init_json_lexer(read_file(CONFIG_FILENAME)));
    json_ast_T* ast = json_parser_parse(parser);

    for (int i = 0; i < ast->key_value_list_size; i++)
    {
        json_ast_T* key_value = ast->key_value_list_value[i];

        if (strcmp(key_value->key_value_key, "window_resizable") == 0)
        {
            config->window_resizable = key_value->key_value_value->integer_value;
            break;  // currently only interested in one value
        }
    }

    json_parser_free(parser);
    json_ast_free(ast);
}
