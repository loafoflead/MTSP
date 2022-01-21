#pragma once

typedef struct
{
    int x, y; // x and y coordinates
} vec2;

// creates and returns a new vec2 with given x and y coords
vec2 V2_new(int x, int y);

// creates and returns a new vec2 ptr
// note: remember to free this memory! uses malloc()
vec2* V2_new_ptr(int x, int y);

// gets the distance between two vectors as a floating point value
// implementation: math.h library sqrtf() function used
float V2_distf(vec2 A, vec2 B);