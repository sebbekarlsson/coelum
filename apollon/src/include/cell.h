#ifndef APOLLON_CELL_H
#define APOLLON_CELL_H
typedef struct CELL_STRUCT
{
    int w;
    int h;
    int selected;
} cell_T;


cell_T* init_cell(int w, int h);
#endif
