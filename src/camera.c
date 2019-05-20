#include "include/camera.h"


camera_T* init_camera()
{
    camera_T* c = calloc(1, sizeof(struct CAMERA_STRUCT));
    c->projection_view = init_projection_view();

    return c;
}
