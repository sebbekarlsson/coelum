#ifndef LETO_ACTOR_IMPL_H
#define LETO_ACTOR_IMPL_H
#include <coelum/actor.h>
#include <coelum/hermes/lexer.h>
#include <coelum/hermes/hermes_parser.h>
#include <coelum/hermes/hermes_runtime.h>


typedef struct ACTOR_IMPL_STRUCT {
    actor_T base;
    char* source_code;
    lexer_T* lexer;
    hermes_parser_T* hermes_parser;
    runtime_T* runtime;
    runtime_reference_T* runtime_reference;
    AST_T* ast_tree;
    AST_T* x_var;
    AST_T* y_var;
} actor_impl_T;


actor_impl_T* init_actor_impl(float x, float y, float z, char* source_code, char* type_name);

void actor_impl_tick(actor_T* self);

void actor_impl_draw(actor_T* self);
#endif
