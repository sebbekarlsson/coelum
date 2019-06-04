#include "include/utils.h"
#include <stdlib.h>
#include <time.h>
#include <cglm/types.h>


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

float to_radians(float angle)
{
    return angle * (GLM_PI / 180.0f);
}
