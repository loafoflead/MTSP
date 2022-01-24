#ifndef VEC
#define VEC 

#include "type.h"

typedef struct
{
    int x, y; // x and y coordinates
} vec2;

typedef struct 
{
    float x, y;
} vec2f;

// checks if two vectors are equal
// impl: returns TRUE if yes, FALSE if no
BOOL V2_cmp(vec2 one, vec2 two);

// same as above only with pointers (so as not to copy the memory)
BOOL V2_cmp_ptr(vec2 *one, vec2 *two);

// creates and returns a new vec2 with given x and y coords
vec2 V2_new(int x, int y);

// creates and returns a new vec2f ptr
// note: remember to free this memory! uses malloc()
vec2* V2_new_ptr(int x, int y);

// same as above but returns copy to a chunk of memory
vec2f V2F_new(float x, float y);

// new vec2f initialised to 0
vec2f V2F_zero();

// add two vec2fs
vec2f V2F_add(vec2f A, vec2f B);

// add two vec2
// note: creates a new variable
vec2 V2_add(vec2 A, vec2 B);

// turn a vec2f into a vec2
// note: creates a new variable
vec2 V2_fromf(vec2f vecf);

// turn a vec2 into a vec2f
// note: creates a new variable
vec2f V2F_fromv2(vec2 vec);

// compare two vec2fs (if equal: TRUE, else: FALSE)
BOOL V2F_cmp_ptr(vec2f *one, vec2f *two);

// dist between two vec2fs
float V2F_dist(vec2f A, vec2f B);

// gets the distance between two vectors as a floating point value
// implementation: math.h library sqrtf() function used
float V2_distf(vec2 A, vec2 B);

#endif
