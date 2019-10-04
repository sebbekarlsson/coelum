#ifndef COELUM_CAMERA_H
#define COELUM_CAMERA_H
#include "projection_view.h"


typedef struct CAMERA_STRUCT
{
    projection_view_T* projection_view;
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;
    float offset_x;
    float offset_y;
    float offset_z;
} camera_T;

camera_T* init_camera(int projection_view_width, int projection_view_height, unsigned int dimensions);

void camera_bind(camera_T* camera);

void camera_unbind(camera_T* camera);

void camera_free(camera_T* camera);
#endif
