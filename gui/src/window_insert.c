#include "include/window_insert.h"
#include "include/select_list.h"
#include <coelum/actor_text.h>
#include <coelum/input.h>
#include <coelum/io.h>
#include <coelum/parsing/lexer.h>
#include <coelum/parsing/config_parser.h>
#include <string.h>


extern keyboard_state_T* KEYBOARD_STATE;

window_insert_T* init_window_insert(float x, float y, void (*on_close)(window_T* self, scene_T* scene))
{
    window_insert_T* window_insert = calloc(1, sizeof(struct WINDOW_insert_STRUCT));
    window_T* window = (window_T*) window_insert;
    window_constructor(window, x, y, 420, 430, "insert", window_insert_tick, window_insert_draw, "window_insert", on_close);

    dynamic_list_T* items = init_dynamic_list(sizeof(struct SELECT_LIST_ITEM_STRUCT));

    lexer_T* lexer = init_lexer(read_file("actors.txt"));
    config_parser_T* parser = init_config_parser(lexer);
    AST_T* node = config_parser_parse(parser);
    dynamic_list_T* actor_names = config_parser_get_keys(node);

    for (int i = 0; i < actor_names->size; i++)
    {
        select_list_item_T* item = init_select_list_item((char*) actor_names->items[i], "0");
        dynamic_list_append(items, item);
    }

    lexer_free(lexer); // we dont need it any more

    window_attach_actor(
        window,
        (actor_T*) init_select_list(
            x - 200 / 2,
            y - ((300 - 64) / 2),
            200,
            300,
            items,
            window
        )        
    );

    return window_insert;
}

void window_insert_tick(actor_T* self)
{
    window_tick(self);
}

void window_insert_draw(actor_T* self)
{
    window_draw(self);
}
