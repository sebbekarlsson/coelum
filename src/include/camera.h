#ifndef COELUM_CAMERA_H
#define COELUM_CAMERA_H
#include "projection_view.h"

typedef struct CAMERA_STRUCT {
    projection_view_T* projection_view;
    float x;
    float y;
    float z;
} camera_T;

camera_T* init_camera();

void camera_bind(camera_T* camera);

void camera_unbind(camera_T* camera);
#endif
