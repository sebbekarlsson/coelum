#include "include/text_field.h"
#include <coelum/theatre.h>
#include <coelum/draw_utils.h>
#include <coelum/text.h>
#include <coelum/input.h>
#include <string.h>


extern theatre_T* THEATRE;
extern keyboard_state_T* KEYBOARD_STATE;

text_field_T* init_text_field(float x, float y, float width, float height, window_T* window)
{
    text_field_T* text_field = calloc(1, sizeof(struct TEXT_FIELD_STRUCT));
    actor_constructor((actor_T*) text_field, x, y, 0.0f, text_field_tick, text_field_draw);

    text_field->width = width;
    text_field->height = height;
    text_field->window = window;
    text_field->focused = 1;
}

void text_field_tick(actor_T* self)
{
    text_field_T* text_field = (text_field_T*) self;

    if (text_field->focused)
    {
        if (strlen(KEYBOARD_STATE->buffer))
        {
            text_field->value = realloc(text_field->value, 1 + strlen(KEYBOARD_STATE->buffer) * sizeof(char));
            strcpy(text_field->value, KEYBOARD_STATE->buffer);
        }
        else
        {
            free(text_field->value);
            text_field->value = calloc(1, sizeof(char));
            text_field->value[0] = '\0';
        }
    }
}

void text_field_draw(actor_T* self)
{
    text_field_T* text_field = (text_field_T*) self;
    state_T* state;

    if (!text_field->window)
    {
        state = (state_T*) scene_manager_get_current_scene(THEATRE->scene_manager);
    }
    else
    {
        state = text_field->window->state;
    }

    float render_x = self->x - text_field->width / 2; 
    float render_y = self->y - text_field->height / 2;

    draw_2D_positioned_2D_mesh(
        render_x,
        render_y,
        text_field->width,
        text_field->height,
        255,
        255,
        255,
        state->VAO,
        state->camera->projection_view
    );

    float size = 5;
    float spacing = 7;

    if (text_field->value)
    {
        draw_text(
            text_field->value,
            self->x - (strlen(text_field->value) * size),
            self->y,
            0.0f,
            60.0f,
            56.0f,
            54.0f,
            size, // size
            spacing, // spacing
            state
        );
    }
}
