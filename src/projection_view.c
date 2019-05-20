#include "include/projection_view.h"
#include <string.h>


projection_view_T* init_projection_view()
{
    projection_view_T* pv = calloc(1, sizeof(struct PROJECTION_VIEW_STRUCT));

    mat4 view =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    mat4 projection =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    memcpy(pv->view, view, sizeof(view));
    memcpy(pv->projection, projection, sizeof(projection));

    glm_translate(pv->view, (vec3){0.0f, 0.0f, 0.0f});
    glm_ortho(0.0f, 640, 480, 0.0f, 0.0f, 1.5f, pv->projection);

    return pv;
}
