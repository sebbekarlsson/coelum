#ifndef COELUM_MATRIX_H
#define COLEUM_MATRIX_H
#include <cglm/types.h>


void matrix_generate(
    float trans_x,
    float trans_y,
    float trans_z,
    float rot_x,
    float rot_y,
    float rot_z,
    float offset_x,
    float offset_y,
    float offset_z,
    mat4 final,
    unsigned int reverse
);
#endif
