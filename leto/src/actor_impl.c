#include "include/actor_impl.h"


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
    impl->lexer = init_lexer(impl->source_code);
    impl->hermes_parser = init_hermes_parser(impl->lexer);
    impl->ast_tree = hermes_parser_parse(impl->hermes_parser, (void*) 0);
    impl->runtime = init_runtime();
    impl->runtime_reference = init_runtime_reference();

    impl->runtime_reference->object->variable_name = "actor";
    hermes_scope_T* scope = init_hermes_scope();
    scope->owner = impl->runtime_reference->object;
    
    // x
    impl->x_var = init_ast(AST_VARIABLE_DEFINITION);
    impl->x_var->variable_name = "x";
    impl->x_var->variable_value = init_ast(AST_INTEGER);
    impl->x_var->variable_type = init_ast(AST_TYPE);
    impl->x_var->variable_type->type_value = "int";
    impl->x_var->variable_value->int_value = a->x;
    dynamic_list_append(scope->variable_definitions, impl->x_var);
    dynamic_list_append(impl->runtime_reference->object->object_children, impl->x_var);

    // y
    impl->y_var = init_ast(AST_VARIABLE_DEFINITION);
    impl->y_var->variable_name = "y";
    impl->y_var->variable_value = init_ast(AST_INTEGER);
    impl->y_var->variable_type = init_ast(AST_TYPE);
    impl->y_var->variable_type->type_value = "int";
    impl->y_var->variable_value->int_value = a->y;
    dynamic_list_append(scope->variable_definitions, impl->y_var);
    dynamic_list_append(impl->runtime_reference->object->object_children, impl->y_var);


    impl->runtime_reference->object->scope = (struct hermes_scope_T*) scope;
    runtime_register_reference(impl->runtime, impl->runtime_reference);

    return impl;
}

void actor_impl_tick(actor_T* self)
{
   actor_tick(self);
   actor_impl_T* actor_impl = (actor_impl_T*) self; 

   if (actor_impl->source_code)
   {
       runtime_visit(actor_impl->runtime, actor_impl->ast_tree);

       self->x = actor_impl->x_var->variable_value->int_value;
       self->y = actor_impl->y_var->variable_value->int_value;
   }
}

void actor_impl_draw(actor_T* self)
{
    actor_draw(self);
}
