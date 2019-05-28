#include "include/select_list.h"
#include <coelum/theatre.h>
#include <coelum/draw_utils.h>
#include <coelum/input.h>
#include <string.h>


extern theatre_T* THEATRE;
extern keyboard_state_T* KEYBOARD_STATE;

extern const float COLOR_BG_DARK_BRIGHT[3];
extern const float COLOR_BG_DARK[3];
extern const float COLOR_FG[3];
extern const float COLOR_BG_BRIGHT[3];

select_list_item_T* init_select_list_item(char* key, char* value)
{
    select_list_item_T* item = calloc(1, sizeof(struct SELECT_LIST_ITEM_STRUCT));
    item->key = key;
    item->value = value;

    return item;
}

select_list_T* init_select_list(float x, float y, float width, float height, dynamic_list_T* items, window_T* window)
{
    select_list_T* select_list = calloc(1, sizeof(struct SELECT_LIST_STRUCT));
    window_component_constructor((window_component_T*) select_list, x, y, select_list_tick, select_list_draw, "select_list");

    select_list->width = width;
    select_list->height = height;
    select_list->items = items;
    select_list->window = window; 
    select_list->selected_index = 0;
    select_list->scroll_position = 0;

    return select_list;
}

void select_list_tick(actor_T* self)
{
    select_list_T* select_list = (select_list_T*) self;
    window_component_T* window_component = (window_component_T*) select_list;

    if (window_component->focused)
    {
        if (KEYBOARD_STATE->keys[GLFW_KEY_DOWN] && KEYBOARD_STATE->key_locks[GLFW_KEY_DOWN] == 0)
        {
            if (select_list->selected_index < select_list->items->size - 1)
            {
                select_list->selected_index += 1;
            }
            else
            {
                select_list->selected_index = 0;
            }

            if (select_list->selected_index * (32 + 8) >= select_list->height)
            {
                select_list->scroll_position += 32.0f;
            }
            else
            {
                select_list->scroll_position = 0.0f;
            }
        
            KEYBOARD_STATE->key_locks[GLFW_KEY_DOWN] = 1;
        }
    }
}

void select_list_draw(actor_T* self)
{
    select_list_T* select_list = (select_list_T*) self;
    state_T* state = (state_T*) scene_manager_get_current_scene(THEATRE->scene_manager);

    const float* color = COLOR_BG_DARK_BRIGHT;

    draw_2D_positioned_2D_mesh(
        self->x,
        self->y,
        select_list->width,
        select_list->height,
        color[0],
        color[1],
        color[2],
        state
    );

    glEnable(GL_SCISSOR_TEST);
    glScissor(self->x, (select_list->height / 2) - self->y + 32, select_list->width, select_list->height);
    for (int i = 0; i < select_list->items->size; i++)
    {
        select_list_item_T* item = (select_list_item_T*) select_list->items->items[i];
        
        const float* text_color = COLOR_FG;

        if (select_list->selected_index == i)
        {
            text_color = COLOR_BG_BRIGHT;

            draw_2D_positioned_2D_mesh(
                self->x,
                self->y + (i * 32) - select_list->scroll_position,
                select_list->width,
                32,
                COLOR_BG_DARK[0],
                COLOR_BG_DARK[1],
                COLOR_BG_DARK[2],
                state
            );
        }

        draw_line(
            self->x,
            self->y + 32 + (32 * i) - select_list->scroll_position,
            0.0f,
            self->x + select_list->width,
            self->y + 32 + (32 * i) - select_list->scroll_position,
            0.0f,
            COLOR_BG_DARK[0],
            COLOR_BG_DARK[1],
            COLOR_BG_DARK[2],
            state
        );

        float size = 6;
        float spacing = 7;
        float left_padding = 4 + size;

        draw_text(
            item->key,
            left_padding + self->x,
            self->y + (((32) * i) + 32 / 2) - select_list->scroll_position,
            0.0f,
            text_color[0],
            text_color[1],
            text_color[2],
            size, // size
            spacing, // spacing
            state
        );
    }
    glDisable(GL_SCISSOR_TEST);
}

select_list_item_T* select_list_get_selected_item(select_list_T* select_list)
{
    return select_list->items->items[select_list->selected_index];
}
