#include "include/matrix.h"
#include <cglm/cglm.h>
#include <cglm/call.h>


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
)
{
    vec4 qx, qy, qz;
    mat4 mx, my, mz;

    glm_quat(qx, glm_rad(rot_x), 1.0f, 0.0f, 0.0f);
    glm_quat(qy, glm_rad(rot_y), 0.0f, 1.0f, 0.0f);
    glm_quat(qz, glm_rad(rot_z), 0.0f, 0.0f, 1.0f);

    glm_quat_mat4(qx, mx);
    glm_quat_mat4(qy, my);
    glm_quat_mat4(qz, mz);

    mat4 trans = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 
    };

    mat4 trans_two = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 
    };

    mat4 trans_pos = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 
    };

    mat4 rot = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    glm_mat4_mulN((mat4* []){&mx, &my, &mz}, 3, rot);

    if (!reverse)
    {
        glm_translate(trans, (vec3){ trans_x+offset_x, trans_y+offset_y, trans_z+offset_z });
        glm_translate(trans_two, (vec3){ -(trans_x+offset_x), -(trans_y+offset_y), -(trans_z+offset_z) });
    }
    else
    {
        glm_translate(trans_two, (vec3){ trans_x+offset_x, trans_y+offset_y, trans_z+offset_z });
        glm_translate(trans, (vec3){ -(trans_x+offset_x), -(trans_y+offset_y), -(trans_z+offset_z) });
    }

    glm_translate(trans_pos, (vec3){ trans_x, trans_y, trans_z });

    glm_mat4_mulN((mat4* []){&trans, &rot, &trans_two, &trans_pos}, 4, final);
}
