#include "include/actor_text.h"
#include "include/input.h"
#include "include/textures.h"
#include "include/text.h"


actor_text* init_actor_text(float x, float y, float z, char* text) {
    actor_text* a_text = calloc(1, sizeof(struct ACTOR_TEXT_STRUCT));

    a_text->text = text;

    actor_constructor((actor*) a_text, x, y, z, actor_text_tick, actor_text_draw);
    return a_text;
};


void actor_text_tick(actor* self) {
}

void actor_text_draw(actor* self) {
    //actor_draw(self);
    render_text(((actor_text*)self)->text, self->x, self->y, self->z);
}