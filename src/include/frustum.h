#ifndef COELUM_FRUSTRUM_H
#define COELUM_FRUSTRUM_H
#include <cglm/cglm.h>


typedef struct FRUSTUM_PLANE_STRUCT
{
    vec3 normal;
    vec3 position;
    float distance;
} frustum_plane_T;

frustum_plane_T* init_frustum_plane();

void frustum_plane_set_normal_and_position(frustum_plane_T* plane, vec3 normal, vec3 position);

float frustum_plane_distance_to_point(frustum_plane_T* plane, vec3 position);

typedef struct FRUSTUM_STRUCT
{
    frustum_plane_T* planes[6];
} frustum_T;

frustum_T* init_frustum();

void frustum_recalc_geometry(float near, float far, float ratio, float angle, vec3 camera_position);

unsigned int frustum_is_point_within(frustum_T* frustum, vec3 position);
#endif
