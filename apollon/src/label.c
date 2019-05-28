#include "include/label.h"
#include <coelum/theatre.h>
#include <coelum/draw_utils.h>
#include <coelum/input.h>
#include <string.h>


extern theatre_T* THEATRE;

extern const float COLOR_FG[3];

label_T* init_label(float x, float y, char* value, window_T* window)
{
    label_T* label = calloc(1, sizeof(struct LABEL_STRUCT));
    window_component_constructor((window_component_T*) label, x, y, label_tick, label_draw, "label");

    label->value = value;
    label->window = window;

    return label;
}

void label_tick(actor_T* self)
{
    actor_tick(self);
}

void label_draw(actor_T* self)
{
    label_T* label = (label_T*) self;
    window_component_T* window_component = (window_component_T*) label;
    state_T* state = (state_T*) scene_manager_get_current_scene(THEATRE->scene_manager);

    float size = 6;
    float spacing = 7;
    float left_padding = 4 + size;

    if (label->value)
    {
        draw_text(
            label->value,
            left_padding + self->x,
            self->y + size / 2,
            0.0f,
            COLOR_FG[0],
            COLOR_FG[1],
            COLOR_FG[2],
            size, // size
            spacing, // spacing
            state
        );

        draw_2D_positioned_2D_mesh(
            self->x,
            self->y + size + (size / 2) + 2,
            strlen(label->value) * (size + spacing) + spacing,
            size / 4,
            COLOR_FG[0],
            COLOR_FG[1],
            COLOR_FG[2],
            state
        );
    }
}
