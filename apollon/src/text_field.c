#include "include/text_field.h"
#include <coelum/theatre.h>
#include <coelum/draw_utils.h>
#include <coelum/input.h>
#include <string.h>


extern theatre_T* THEATRE;
extern keyboard_state_T* KEYBOARD_STATE;

extern const float COLOR_FG[3];
extern const float COLOR_CONTRAST[3];

text_field_T* init_text_field(float x, float y, float width, float height, window_T* window)
{
    text_field_T* text_field = calloc(1, sizeof(struct TEXT_FIELD_STRUCT));
    window_component_constructor((window_component_T*) text_field, x, y, text_field_tick, text_field_draw, "text_field");

    text_field->width = width;
    text_field->height = height;
    text_field->window = window;

    return text_field;
}

void text_field_tick(actor_T* self)
{
    text_field_T* text_field = (text_field_T*) self;
    window_component_T* window_component = (window_component_T*) text_field;

    if (window_component->focused)
    {
        KEYBOARD_STATE->key_locks[GLFW_KEY_C] = 1;
        KEYBOARD_STATE->key_locks[GLFW_KEY_Q] = 1;
        KEYBOARD_STATE->key_locks[GLFW_KEY_I] = 1;

        keyboard_state_inread(KEYBOARD_STATE, &text_field->value);
    }
}

void text_field_draw(actor_T* self)
{
    text_field_T* text_field = (text_field_T*) self;
    window_component_T* window_component = (window_component_T*) text_field;
    state_T* state = (state_T*) scene_manager_get_current_scene(THEATRE->scene_manager);

    draw_2D_positioned_2D_mesh(
        self->x,
        self->y,
        text_field->width,
        text_field->height,
        255,
        255,
        255,
        state
    );

    float size = 6;
    float spacing = 7;
    float left_padding = 4 + size;

    if (text_field->value)
    {
        //glEnable(GL_SCISSOR_TEST);
        //glScissor(self->x, self->y - text_field->height, text_field->width, text_field->height);
        draw_text(
            text_field->value,
            left_padding + self->x,
            self->y + text_field->height / 2,
            0.0f,
            COLOR_FG[0],
            COLOR_FG[1],
            COLOR_FG[2],
            size, // size
            spacing, // spacing
            state
        );
        //glDisable(GL_SCISSOR_TEST);
    }

    if (window_component->focused)
    {
        draw_2D_positioned_2D_mesh(
            self->x,
            self->y + text_field->height,
            text_field->width,
            text_field->height / 4,
            COLOR_CONTRAST[0],
            COLOR_CONTRAST[1],
            COLOR_CONTRAST[2],
            state
        );
    }
}
