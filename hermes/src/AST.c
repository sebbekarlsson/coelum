#include "include/AST.h"
#include <stdlib.h>
#include <string.h>


AST_T* init_ast(int type)
{
    AST_T* AST = calloc(1, sizeof(struct AST_STRUCT));
    AST->type = type;

    return AST;
}
