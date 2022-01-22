#ifndef BD
#define BD 0

#include "vec2.h"
// draws a circle at a center point given and a given radius
// takes: center point, radius, and character to draw
// implementation: creates a square and cuts the circle out of it
void BD_draw_circle(vec2 center, int radius, char to_put);

// same function as before, but draws in the rest of the square as the highlight character
void BD_draw_circle_highlighted(vec2 center, int radius, char to_put, char highlight);

// places a point at a given x y pos on the screen
// implementation: uses ncurses move(y, x) and addch(char) functions
// note: uses in_bounds() from simulation.h, if out of bounds will return
void BD_draw_point(char to_draw, int x, int y);

// draws a square, and then uses the index given to get a point on that square
// takes: center of the square (top left corner)
// radius: radius of the square
// index: index on the square (going from top to bottom row and left to right collumn)
vec2 BD_V2_ind_on_square(vec2 center, int radius, int index);

// same as previous function, only it takes x and y ints as opposed to a struct
vec2 BD_ind_on_square(int x, int y, int radius, int index);

#endif