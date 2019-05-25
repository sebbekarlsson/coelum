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
    actor_constructor((actor_T*) text_field, x, y, 0.0f, text_field_tick, text_field_draw);

    text_field->width = width;
    text_field->height = height;
    text_field->window = window;
    text_field->focused = 0;
}

void text_field_tick(actor_T* self)
{
    text_field_T* text_field = (text_field_T*) self;

    if (text_field->focused)
    {
        KEYBOARD_STATE->key_locks[GLFW_KEY_C] = 1;
        KEYBOARD_STATE->key_locks[GLFW_KEY_Q] = 1;
        KEYBOARD_STATE->key_locks[GLFW_KEY_I] = 1;

        keyboard_state_inread(KEYBOARD_STATE, &text_field->value);

        if (KEYBOARD_STATE->keys[GLFW_KEY_ENTER] && KEYBOARD_STATE->key_locks[GLFW_KEY_ENTER] == 0)
        {
            text_field->focused = 0;
            KEYBOARD_STATE->key_locks[GLFW_KEY_C] = 0;
            KEYBOARD_STATE->key_locks[GLFW_KEY_Q] = 0;
            KEYBOARD_STATE->key_locks[GLFW_KEY_I] = 0;

            KEYBOARD_STATE->key_locks[GLFW_KEY_ENTER] = 1;
        }
    }
    else
    {
        if (KEYBOARD_STATE->keys[GLFW_KEY_ENTER] && KEYBOARD_STATE->key_locks[GLFW_KEY_ENTER] == 0)
        {
            text_field->focused = 1;
            keyboard_state_copy_buffer(KEYBOARD_STATE, text_field->value);
            KEYBOARD_STATE->key_locks[GLFW_KEY_ENTER] = 1;
        }
    }
}

void text_field_draw(actor_T* self)
{
    text_field_T* text_field = (text_field_T*) self;
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
        glEnable(GL_SCISSOR_TEST);
        glScissor(self->x, self->y - text_field->height, text_field->width, text_field->height);
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
        glDisable(GL_SCISSOR_TEST);
    }

    if (text_field->focused)
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
