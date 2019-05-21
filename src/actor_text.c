#include "include/actor_text.h"
#include "include/input.h"
#include "include/textures.h"
#include "include/text.h"


/**
 * Creates an instancec of a text actor.
 *
 * @param float x
 * @param float y
 * @param float z
 * @param char* text
 *
 * @return actor_text_T*
 */
actor_text_T* init_actor_text(float x, float y, float z, char* text, float r, float g, float b)
{
    actor_text_T* a_text = calloc(1, sizeof(struct ACTOR_TEXT_STRUCT));

    a_text->text = text;
    a_text->r = r;
    a_text->g = g;
    a_text->b = b;

    actor_constructor((actor_T*) a_text, x, y, z, actor_text_tick, actor_text_draw);
    return a_text;
}


void actor_text_tick(actor_T* self)
{
    // silence
}

void actor_text_draw(actor_T* self)
{
    actor_text_T* a_t = (actor_text_T*) self;

    draw_text(((actor_text_T*)self)->text, self->x, self->y, self->z, a_t->r, a_t->g, a_t->b);
}
