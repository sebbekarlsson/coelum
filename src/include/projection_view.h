#ifndef COELUM_PROJECTION_VIEW_H
#define COELUM_PROJECTION_VIEW_H
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct PROJECTION_VIEW_STRUCT {
    unsigned uniform_mat4_projection;
    unsigned uniform_mat4_view;
    mat4 projection;
    mat4 view;
} projection_view_T;

projection_view_T* init_projection_view();
#endif
