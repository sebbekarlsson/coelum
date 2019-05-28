#include "include/cell.h"
#include <stdlib.h>


cell_T* init_cell(int w, int h)
{
    cell_T* cell = calloc(1, sizeof(struct CELL_STRUCT));
    cell->w = w;
    cell->h = h;
    cell->selected = 0;

    return cell;
}
