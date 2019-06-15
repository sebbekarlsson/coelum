#include "include/actor_light.h"
#include "include/input.h"
#include "include/draw_utils.h"
#include "include/theatre.h"


extern theatre_T* THEATRE;

/**
 * Creates an instancec of a light actor.
 *
 * @param float x
 * @param float y
 * @param float z
 * @param float intensity
 *
 * @return actor_light_T*
 */
actor_light_T* init_actor_light(float x, float y, float z, float intensity)
{
    actor_light_T* a_light = calloc(1, sizeof(struct ACTOR_LIGHT_STRUCT));
    actor_constructor((actor_T*) a_light, x, y, z, actor_light_tick, actor_light_draw, "light");

    a_light->intensity = intensity;

    return a_light;
}

void actor_light_tick(actor_T* self)
{
    // silence
}

void actor_light_draw(actor_T* self)
{
    scene_T* scene = scene_manager_get_current_scene(THEATRE->scene_manager);
    state_T* state = (state_T*) scene;

    draw_3D_axis(
        self->x,
        self->y,
        self->z,
        8,
        8,
        8,
        state
    );
}
