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
    camera_T* camera;
    void (*tick)(void* self);
    void (*draw)(void* self);
} state_T;

state_T* init_state();

state_T* state_constructor(state_T* state, void (*tick)(state_T* self), void (*draw)(state_T* self), int projection_view_width, int projection_view_height);

void state_tick(state_T* state);

void state_draw(state_T* state);
#endif
