#include "include/scene_impl.h"
#include <coelum/theatre.h>
#include <coelum/textures.h>
#include <coelum/actor.h>
#include <coelum/io.h>
#include <coelum/hermes/lexer.h>
#include <coelum/hermes/hermes_parser.h>
#include <coelum/hermes/hermes_runtime.h>
#include <string.h>


extern theatre_T* THEATRE;

actor_abstract_T* init_actor_abstract(char* type_name, float x, float y, float z)
{
    actor_abstract_T* actor_abstract = calloc(1, sizeof(struct ACTOR_ABSTRACT_STRUCT));
    actor_abstract->type_name = type_name;
    actor_abstract->x = x;
    actor_abstract->y = y;
    actor_abstract->z = z;
}

void scene_impl_load(scene_T* scene)
{
    state_T* state = (state_T*) scene;
    scene_impl_T* scene_impl = (scene_impl_T*) scene;

    // lets lookup actor definitions
    lexer_T* lexer = init_lexer(read_file("actors.txt"));
    hermes_parser_T* parser = init_hermes_parser(lexer);
    AST_T* actors_node = hermes_parser_parse(parser, (void*) 0);
    runtime_T* runtime = init_runtime();
    runtime_visit(runtime, actors_node);
    hermes_scope_T* runtime_scope = get_scope(runtime, actors_node);

    //dynamic_list_T* actor_names = hermes_parser_get_keys(actors_node);

    for (int x = 0; x < scene_impl->on_load_actors->size; x++)
    {
        actor_abstract_T* actor_abstract = (actor_abstract_T*) scene_impl->on_load_actors->items[x];

        for (int i = 0; i < runtime_scope->variable_definitions->size; i++)
        {
            AST_T* ast_vardef = (AST_T*) runtime_scope->variable_definitions->items[i];

            hermes_scope_T* object_scope = get_scope(runtime, ast_vardef->variable_value);

            char* actor_name = (char*) ast_vardef->variable_name;

            if (!(strcmp(actor_name, actor_abstract->type_name) == 0))
                continue;

            printf("Loading actor `%s`\n", actor_name);

            char* actor_texture_path;
            float actor_width;
            float actor_height;

            for (int j = 0; j < object_scope->variable_definitions->size; j++)
            {
                AST_T* ast_obj_var = (AST_T*) object_scope->variable_definitions->items[j];

                if (strcmp(ast_obj_var->variable_name, "texture"))
                    actor_texture_path = ast_obj_var->variable_value->string_value;
                if (strcmp(ast_obj_var->variable_name, "width"))
                    actor_width = ast_obj_var->variable_value->int_value;
                if (strcmp(ast_obj_var->variable_name, "height"))
                    actor_height = ast_obj_var->variable_value->int_value;
            } 

            actor_T* actor = init_actor(0.0f, 0.0f, 0.0f);
            actor_constructor(actor, actor_abstract->x, actor_abstract->y, actor_abstract->z, actor_tick, actor_draw, actor_abstract->type_name);
            actor->width = actor_width;
            actor->height = actor_height;
            texture_T* texture = get_texture(actor_texture_path, GL_RGBA);
            actor->texture = texture->renderable_texture;

            // finally add the actor to the scene state.
            dynamic_list_append(state->actors, actor);
        }
    }

    lexer_free(lexer);
    free(parser);
    free(actors_node);
}

/**
 * Creates a new scene_impl
 *
 * @return scene_impl_T*
 */
scene_impl_T* init_scene_impl()
{
    scene_impl_T* s_impl = calloc(1, sizeof(struct SCENE_IMPL_STRUCT));
    scene_T* s = (scene_T*) s_impl;

    scene_constructor(s, scene_impl_tick, scene_impl_draw);

    s_impl->on_load_actors = init_dynamic_list(sizeof(struct ACTOR_ABSTRACT_STRUCT));

    s->load = scene_impl_load;

    return s_impl;
}

void scene_impl_tick(state_T* state)
{
    scene_tick((scene_T*) state);
}

void scene_impl_draw(state_T* state)
{
    scene_draw((scene_T*) state);
}
