#include "vec2.h"
#include "type.h"

#include <stdlib.h>
#include <math.h>

vec2f V2F_new(float x, float y)
{
    vec2f new = {x, y};
    return new;
}

vec2f *V2F_new_ptr(float x, float y)
{
    vec2f *new = (vec2f*) malloc(sizeof(vec2f));
    return new;
}

BOOL V2F_cmp_ptr(vec2f *one, vec2f *two)
{
    if (one->x == two->x && one->y == two->y)
    {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

float V2F_dist(vec2f A, vec2f B)
{
    float dist = sqrtf((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
    return dist;
}

vec2f V2F_add(vec2f A, vec2f B)
{
		vec2f new = {A.x + B.x, A.y + B.y};
		return new;
}

vec2f V2F_zero()
{
		vec2f new = {0,0};
		return new;
}

vec2 V2_add(vec2 A, vec2 B)
{
		vec2 new = {A.x + B.x, A.y + B.y};
		return new;
}

vec2f V2F_fromv2(vec2 vec)
{
		vec2f new = {vec.x, vec.y};
		return new;
}

vec2 V2_fromf(vec2f vecf)
{
		vec2 new = {(int) vecf.x, (int) vecf.y};
		return new;
}


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
