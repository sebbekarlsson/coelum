#ifndef COELUM_FRUSTRUM_H
#define COELUM_FRUSTRUM_H
#include <cglm/cglm.h>


typedef struct FRUSTUM_STRUCT
{
    vec4 planes[6];
    vec4 corners[8];
    vec4 center;
} frustum_T;

frustum_T* init_frustum();

void frustum_recalc_geometry(frustum_T* frustum, mat4 projection, mat4 view);
#endif
