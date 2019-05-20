#ifndef COELUM_PROJECTION_VIEW_H
#define COELUM_PROJECTION_VIEW_H
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct PROJECTION_VIEW_STRUCT
{
    mat4 projection;
    mat4 view;
} projection_view_T;

projection_view_T* init_projection_view();

void projection_view_translate(projection_view_T* projection_view, float x, float y, float z);
#endif
