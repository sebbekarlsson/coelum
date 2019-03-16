#include "include/actor.h"
#include <stdio.h>
#include <stdlib.h>


actor* init_actor(float x, float y, float z) {
    actor* a = calloc(1, sizeof(struct ACTOR_STRUCT));
    a->x = x;
    a->y = y;
    a->z = z;

    return a;
}

void tick_actor(actor* a) {
    printf("Tick actor!\n");
}

void draw_actor(actor* a) {
    printf("Tick actor!\n");
}
