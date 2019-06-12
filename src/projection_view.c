#include "include/projection_view.h"
#include "include/constants.h"
#include "include/utils.h"
#include <cglm/cglm.h>
#include <cglm/call.h>
#include <string.h>


/**
 * Create a new projection_view
 *
 * @param int width
 * @param int height
 *
 * @return projection_view_T*
 */
projection_view_T* init_projection_view(int width, int height, unsigned int dimensions)
{
    projection_view_T* pv = calloc(1, sizeof(struct PROJECTION_VIEW_STRUCT));
    pv->dimensions = dimensions;

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

    if (pv->dimensions == 2)
    { // we are doing 2D
        glm_ortho(0.0f, width, height, 0.0f, 0.0f, 1.5f, pv->projection);
    }
    else
    { // we are doing 3D
        glm_perspective(glm_rad(45.0f), (float) width / (float)height, 0.01f, 1000.0f, pv->projection);
        /*glm_lookat(
            (vec3){0, 0, 0},
            (vec3){0, 0, 0},
            (vec3){0, 1, 0},
            pv->view
        );*/
    } 
    return pv;
}

/**
 * Translate a projection_view on the 3rd dimension.
 *
 * @param projection_view_T* projection_view
 * @param float x
 * @param float y
 * @param float z
 */
void projection_view_translate(projection_view_T* projection_view, float x, float y, float z)
{
    glm_translate(projection_view->view, (vec3){x, y, z});
}

/**
 * Deallocator for `projection_view` object.
 *
 * @param projection_view_T* projection_view
 */
void projection_view_free(projection_view_T* projection_view)
{
    free(projection_view);
}
