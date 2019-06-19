#include "include/physics.h"


/**
 * Mainly used for physics.
 * This method will decrease the value of a variable until
 * it becomes `0` (zero).
 *
 * @param float* value
 * @param float friction
 */
void physics_to_zero(float* value, float friction)
{
    if (*value > 0) {
        if (*value - friction < 0) {
            *value = 0.0f;
        } else {
            *value -= friction;
        }
    }

    if (*value < 0) {
        if (*value + friction > 0) {
            *value = 0.0f;
        } else {
            *value += friction;
        }
    }
}

/**
 * Updates the physical behavior of an actor.
 *
 * @param actor_T* actor
 */
void physics_tick_actor(actor_T* actor)
{
    actor->x += actor->dx;
    actor->y += actor->dy;
    actor->z += actor->dz;

    physics_to_zero(&actor->dx, actor->friction);
    physics_to_zero(&actor->dy, actor->friction);
    physics_to_zero(&actor->dz, actor->friction);
}


/**
 * Push a vec2 in a certain direction.
 *
 * @param float* x
 * @param float* y
 * @param float angle
 * @param float length
 */
void physics_vec2_push(float* x, float* y, float angle, float length)
{
    float radians = glm_rad(angle);

    *x += cos(radians) * length;
    *y -= sin(radians) * length;
} 
