#include "include/utils.h"
#include <stdlib.h>
#include <time.h>
#include <cglm/types.h>
#include <math.h>


/**
 * Generate new "seed" for the rand function.
 */
void init_random()
{
    srand(time((void*) 0));
}

/**
 * Get a random integer in a range
 *
 * @param int min_value
 * @param int max_value
 */
int random_int(int min_value, int max_value)
{
   return min_value + rand() % (max_value+1 - min_value);
}

/**
 * Calculate the distance between 2 2D vectors
 *
 * @param float x1
 * @param float y1
 * @param float x2
 * @param float y2
 *
 * @return float
 */
float vec2_distance(float x1, float y1, float x2, float y2)
{
    return hypot(x2 - x1, y2 - y1);
}

/**
 * Calculate the angle between 2 2D vectors
 *
 * @param float x1
 * @param float y1
 * @param float x2
 * @param float y2
 *
 * @return float
 */
float vec2_angle(float x1, float y1, float x2, float y2)
{
    return atan2(y2 - y1, x2 - x1) * (180.0 / GLM_PI);
}

/**
 * Normalize an angle to be in the range of 0 - 360.
 *
 * @param float angle
 *
 * @return float
 */
float normalize_angle(float angle)
{
    if (angle < 0)
        angle += 360.0f;

    return angle;
}
