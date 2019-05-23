#include "include/camera.h"


camera_T* init_camera(int projection_view_width, int projection_view_height)
{
    camera_T* c = calloc(1, sizeof(struct CAMERA_STRUCT));
    c->projection_view = init_projection_view(projection_view_width, projection_view_height);

    c->x = 0.0f;
    c->y = 0.0f;
    c->z = 0.0f;

    return c;
}

/**
 * Bind camera, called when you want to render something within the scope of
 * a camera, if used; make sure to call camera_unbind when done.
 * This function modifies the translation to the camera position.
 *
 * @param camera_T* camera
 */
void camera_bind(camera_T* camera)
{
    glm_translate(camera->projection_view->view, (vec3){-camera->x, -camera->y, -camera->z});
}

/**
 * To be called after camera_bind has been called.
 * This resets the translation.
 *
 * @param camera_T* camera
 */
void camera_unbind(camera_T* camera)
{
    glm_translate(camera->projection_view->view, (vec3){camera->x, camera->y, camera->z});
}
