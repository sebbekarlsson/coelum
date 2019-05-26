#include "include/window_insert.h"
#include "include/text_field.h"
#include <coelum/actor_text.h>
#include <coelum/input.h>


extern keyboard_state_T* KEYBOARD_STATE;

window_insert_T* init_window_insert(float x, float y)
{
    window_insert_T* window_insert = calloc(1, sizeof(struct WINDOW_insert_STRUCT));
    window_constructor((window_T*) window_insert, x, y, 420, 430, "insert", window_insert_tick, window_insert_draw, "window_insert");

    return window_insert;
}

void window_insert_tick(actor_T* self)
{
    window_tick(self);
}

void window_insert_draw(actor_T* self)
{
    window_draw(self);
}
