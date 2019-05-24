#include "include/grid.h"
#include <coelum/draw_utils.h>
#include <coelum/theatre.h>
#include <coelum/utils.h>


extern theatre_T* THEATRE;

extern const float COLOR_BG_DARK[3];

grid_T* init_grid()
{
    grid_T* grid = calloc(1, sizeof(struct GRID_STRUCT));

    for (int x = 0; x < WINDOW_WIDTH / 16; x++)
    {
        for (int y = 0; y < WINDOW_HEIGHT/ 16; y++)
        {
            grid->cells[x][y] = init_cell(16, 16);
        }
    }

    grid->cursor_x = (WINDOW_WIDTH / 16) / 2;
    grid->cursor_y = (WINDOW_HEIGHT / 16) / 2;

    return grid;
}

void grid_tick(grid_T* grid)
{
    // just for the goofs and giggles, testing stuff
    /*for (int x = 0; x < WINDOW_WIDTH / 16; x++)
    {
        for (int y = 0; y < WINDOW_HEIGHT/ 16; y++)
        {
            cell_T* cell = grid->cells[x][y];

            if (random_int(0, 3) == 0)
            {
                if (!cell->selected)
                    cell->selected = 1;
                else
                    cell->selected = 0;
            }
        }
    }*/
}

void grid_draw(grid_T* grid)
{
    scene_T* scene = scene_manager_get_current_scene(THEATRE->scene_manager);
    state_T* state = (state_T*) scene;

    for (int x = 0; x < WINDOW_WIDTH / 16; x++)
    {
        float cell_x = x * 16;

        float r = COLOR_BG_DARK[0];
        float g = COLOR_BG_DARK[1];
        float b = COLOR_BG_DARK[2];

        draw_line(
            cell_x,
            0.0f,
            0.0f,
            cell_x,
            WINDOW_HEIGHT,
            0.0f,
            r,
            g,
            b,
            state->VAO,
            state->camera->projection_view
        );

        for (int y = 0; y < WINDOW_HEIGHT/ 16; y++)
        {
            cell_T* cell = grid->cells[x][y];

            float cell_y = y * 16;

            if (cell_x == 0)
            {
                draw_line(
                    0.0,
                    cell_y,
                    0.0f,
                    WINDOW_WIDTH,
                    cell_y,
                    0.0f,
                    r,
                    g,
                    b,
                    state->VAO,
                    state->camera->projection_view
                );
            }

            if (grid->cursor_x == x && grid->cursor_y == y)
            {
                draw_2D_positioned_2D_mesh(
                    cell_x,
                    cell_y,
                    16,
                    16,
                    r,
                    g,
                    b,
                    state->VAO,
                    state->camera->projection_view
                );
            }
            else
            if (cell->selected)
            {
                draw_2D_positioned_2D_mesh(
                    cell_x,
                    cell_y,
                    16,
                    16,
                    r,
                    g,
                    b,
                    state->VAO,
                    state->camera->projection_view
                );
            }
        }
    }
}

void grid_unselect(grid_T* grid)
{
    for (int x = 0; x < WINDOW_WIDTH / 16; x++)
    {
        for (int y = 0; y < WINDOW_HEIGHT/ 16; y++)
        {
            grid->cells[x][y]->selected = 0;
        }
    }
}
