#include "vec2.h"
#include "type.h"

#include <stdlib.h>
#include <math.h>

BOOL V2_cmp(vec2 one, vec2 two)
{
    if (one.x == two.x && one.y == two.y)
    {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

BOOL V2_cmp_ptr(vec2 *one, vec2 *two)
{
    if (one->x == two->x && one->y == two->y)
    {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

vec2 V2_new(int x, int y)
{
    vec2 new_vec = {x, y};
    return new_vec;
}

vec2* V2_new_ptr(int x, int y)
{
    vec2* new_vec_ptr = (vec2*) malloc(sizeof(vec2));
    new_vec_ptr->x = x;
    new_vec_ptr->y = y;
    return new_vec_ptr;
}

float V2_distf(vec2 A, vec2 B)
{
    float dist = sqrtf((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
    return dist;
}