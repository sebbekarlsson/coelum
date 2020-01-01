#include "include/frustum.h"
#include <string.h>


frustum_T* init_frustum()
{
    frustum_T* frustum = calloc(1, sizeof(struct FRUSTUM_STRUCT));
    return frustum;
}

void frustum_recalc_geometry(frustum_T* frustum, mat4 projection, mat4 view)
{
    //mat4 invViewProj;

    //glm_mat4_inv(cam->viewProj, invViewProj);
    mat4 viewProj, invViewProj;
    glm_mat4_mul(projection, view, viewProj);

    glm_frustum_planes(viewProj,        frustum->planes);

    glm_mat4_inv(viewProj, invViewProj);
    glm_frustum_corners(invViewProj,         frustum->corners);
    glm_frustum_center(frustum->corners, frustum->center);
}
