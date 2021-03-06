#ifndef COELUM_CAMERA_H
#define COELUM_CAMERA_H
#include "projection_view.h"
#include "frustum.h"


typedef struct CAMERA_STRUCT
{
    projection_view_T* projection_view;
    frustum_T* frustum;
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;
    float offset_x;
    float offset_y;
    float offset_z;
    unsigned int reverse;
} camera_T;

camera_T* init_camera(int projection_view_width, int projection_view_height, unsigned int dimensions);

void camera_bind(camera_T* camera);

void camera_unbind(camera_T* camera);

void camera_free(camera_T* camera);
#endif
