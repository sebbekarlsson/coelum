#ifndef COELUM_CAMERA_H
#define COELUM_CAMERA_H
#include "projection_view.h"

typedef struct CAMERA_STRUCT {
    projection_view_T* projection_view;
} camera_T;

camera_T* init_camera();
#endif
