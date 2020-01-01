#include "include/frustum.h"
#include <string.h>


frustum_plane_T* init_frustum_plane()
{
    frustum_plane_T* plane = calloc(1, sizeof(struct FRUSTUM_PLANE_STRUCT));
    plane->distance = 0.0f;
    
    return plane;
}

void frustum_plane_set_normal_and_position(frustum_plane_T* plane, vec3 normal, vec3 position)
{
    glm_vec3_copy(normal, plane->normal);
    glm_vec3_copy(position, plane->position);
}

float frustum_plane_distance_to_point(frustum_plane_T* plane, vec3 position)
{

}

frustum_T* init_frustum()
{
    frustum_T* frustum = calloc(1, sizeof(struct FRUSTUM_STRUCT));

    // near plane
    frustum->planes[0] = init_frustum_plane((vec3){0.0f, 0.0f, 1.0f});

    // far plane
    frustum->planes[1] = init_frustum_plane((vec3){0.0f, 0.0f, -1.0f});
    
    // left plane
    frustum->planes[2] = init_frustum_plane((vec3){-1.0f, 0.0f, 0.0f});

    // right plane
    frustum->planes[3] = init_frustum_plane((vec3){1.0f, 0.0f, 0.0f});

    // top plane
    frustum->planes[4] = init_frustum_plane((vec3){0.0f, 1.0f, 0.0f});

    // bottom plane
    frustum->planes[5] = init_frustum_plane((vec3){0.0f, -1.0f, 0.0f});
}

void frustum_recalc_geometry(float near, float far, float ratio, float angle, vec3 camera_position)
{
}

unsigned int frustum_is_point_within(frustum_T* frustum, vec3 position)
{
	for(int i=0; i < 6; i++)
    {
        frustum_plane_T* plane = frustum->planes[i];

		if (frustum_plane_distance_to_point(frustum, position) < 0)
			return 0;
	}

	return 1;
}
