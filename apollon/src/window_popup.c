#include "include/window_popup.h"
#include "include/text_field.h"
#include "include/label.h"
#include <coelum/draw_utils.h>
#include <coelum/theatre.h>
#include <string.h>


extern theatre_T* THEATRE;

extern const float COLOR_FG[3];

window_popup_T* init_window_popup(float x, float y, char* message, void (*on_close)(window_T* self, scene_T* scene))
{
    window_popup_T* window_popup = calloc(1, sizeof(struct WINDOW_POPUP_STRUCT));
    window_constructor((window_T*) window_popup, x, y, 420, 430, "popup", window_popup_tick, window_popup_draw, "window_popup", on_close);

    window_popup->message = message;

    return window_popup;
}

void window_popup_tick(actor_T* self)
{
    window_tick(self);
}

void window_popup_draw(actor_T* self)
{
    window_T* window = (window_T*) self;
    window_popup_T* window_popup = (window_popup_T*) window;
    state_T* state = (state_T*) scene_manager_get_current_scene(THEATRE->scene_manager);

    window_draw(self);

    float size = 6;
    float spacing = 7;
    float left_padding = 4 + size;

    draw_text(
        window_popup->message,
        self->x - (strlen(window_popup->message) * (size + spacing)) / 2,
        self->y,
        0.0f,
        COLOR_FG[0],
        COLOR_FG[1],
        COLOR_FG[2],
        size, // size
        spacing, // spacing
        state
    );
}
