#ifndef COELUMG_GRID_H
#define COELUMG_GRID_H
#include "cell.h"
#include <coelum/constants.h>

typedef struct GRID_STRUCT
{
    cell_T* cells[WINDOW_WIDTH / 16][WINDOW_HEIGHT / 16];
} grid_T;

grid_T* init_grid();

void grid_tick(grid_T* grid);

void grid_draw(grid_T* grid);
#endif
