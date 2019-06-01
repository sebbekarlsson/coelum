#include "include/actor_impl.h"
#include <coelum/hermes/lexer.h>
#include <coelum/hermes/hermes_parser.h>
#include <coelum/hermes/hermes_runtime.h>


/**
 * Creates an instancec of a impl actor.
 *
 * @param float x
 * @param float y
 * @param float z
 * @param char* source_code
 * @param char* type_name
 *
 * @return actor_impl_T*
 */
actor_impl_T* init_actor_impl(float x, float y, float z, char* source_code, char* type_name)
{
    actor_impl_T* impl = calloc(1, sizeof(struct ACTOR_IMPL_STRUCT));
    actor_T* a = (actor_T*) impl;

    actor_constructor(a, x, y, z, actor_impl_tick, actor_impl_draw, type_name);

    impl->source_code = source_code;

    return impl;
}

void actor_impl_tick(actor_T* self)
{
   actor_tick(self);
   actor_impl_T* actor_impl = (actor_impl_T*) self; 

   if (actor_impl->source_code)
   {
       lexer_T* lexer = init_lexer(actor_impl->source_code);
       hermes_parser_T* parser = init_hermes_parser(lexer);
       AST_T* node = hermes_parser_parse(parser, (void*) 0);
       runtime_T* runtime = init_runtime();

       runtime_reference_T* runtime_reference = init_runtime_reference();
       runtime_reference->object->variable_name = "actor";
       hermes_scope_T* scope = init_hermes_scope();
       scope->owner = runtime_reference->object;
       runtime_reference->object->scope = (struct hermes_scope_T*) scope;

       AST_T* xdef = init_ast(AST_VARIABLE_DEFINITION);
       xdef->variable_name = "x";
       xdef->variable_value = init_ast(AST_INTEGER);
       xdef->variable_value->int_value = self->x;
       dynamic_list_append(runtime_reference->object->object_children, xdef);
       dynamic_list_append(scope->variable_definitions, xdef);
       runtime_register_reference(runtime, runtime_reference);


       runtime_visit(runtime, node);

       free(lexer);

       if (parser->prev_token)
       {
           free(parser->prev_token);
       }


       if (parser->current_token)
       {
           free(parser->current_token);
       }

       free(node);
   }
}

void actor_impl_draw(actor_T* self)
{
    actor_draw(self);
}
