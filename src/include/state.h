#ifndef COELUM_STATE_H
#define COELUM_STATE_H
#include "dynamic_list.h"
#include "camera.h"

/**
 * This definition is very abstract, I am having difficulties explaining what
 * it is, but it is basically a very slimmed down version of a Scene.
 *
 * Maybe you can see it as a "rendering area" or something.
 */
typedef struct STATE_STRUCT
{
    dynamic_list_T* actors;
    unsigned int VAO;
    unsigned int lighting_enabled;
    camera_T* camera;
} state_T;

state_T* init_state();

state_T* state_constructor(state_T* state, int projection_view_width, int projection_view_height, unsigned int dimensions);

void state_tick(state_T* state);

void state_draw(state_T* state);

void state_free(state_T* state);
#endif
