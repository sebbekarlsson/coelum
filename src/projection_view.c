#include "include/projection_view.h"
#include "include/constants.h"
#include <string.h>


projection_view_T* init_projection_view(int width, int height)
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

    projection_view_translate(pv, 0.0f, 0.0f, 0.0f);
    glm_ortho(0.0f, width, height, 0.0f, 0.0f, 1.5f, pv->projection);

    return pv;
}

void projection_view_translate(projection_view_T* projection_view, float x, float y, float z)
{
    glm_translate(projection_view->view, (vec3){x, y, z});
}
