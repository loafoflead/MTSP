#ifndef VEC
#define VEC 

#include "type.h"

typedef struct
{
    int x, y; // x and y coordinates
} vec2;

// checks if two vectors are equal
// impl: returns TRUE if yes, FALSE if no
BOOL V2_cmp(vec2 one, vec2 two);

// same as above only with pointers (so as not to copy the memory)
BOOL V2_cmp_ptr(vec2 *one, vec2 *two);

// creates and returns a new vec2 with given x and y coords
vec2 V2_new(int x, int y);

// creates and returns a new vec2 ptr
// note: remember to free this memory! uses malloc()
vec2* V2_new_ptr(int x, int y);

// gets the distance between two vectors as a floating point value
// implementation: math.h library sqrtf() function used
float V2_distf(vec2 A, vec2 B);

#endif