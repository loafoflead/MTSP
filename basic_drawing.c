#include <ncurses.h>
#include <stdio.h>

#include "vec2.h"

// void BD_draw_cicle(vec2 center, int radius, char to_put)
// {
//     int N = 2 * radius + 1; // square that encompasses the circle (diameter plus one for some reason)

//     int x,y;

//     for (int i = center.x; i < N; i ++)
//     {
//         for (int j = center.y; j < N; j ++)
//         {
//             x = i - radius; 
//             y = j - radius; // start from the top left corner

//             if ( (x * x) + (y * y) <= (radius*radius) + 1 ) // if the point is in the circle, place it and advance the cursor
//             {
//                 addch(to_put); 
//             }
//             else // if not, simply advance the cursor
//             {
//                 addch(' ');
//             }
//             addch(' ');
//         }
//         addch('\n'); // newline when reaching new row (column?)
//     }
// }

void BD_draw_circle(vec2 center, int radius, char to_put)
{
    int max_index = center.x + radius + 1; // get the maxiumum radius of the square

    for (int i = center.x - radius; i < max_index; i ++) // begin counter center minus radius to get a full circle with the center as its center
    {
        for (int j = center.y - radius; j < max_index; j ++)
        {
            vec2 current_position = {i, j}; // get a vec of the current position
            if (V2_distf(center, current_position) < (float) radius) // if the distance is less than the radius draw it
            {
                move(j, i);
                addch(to_put);
            }
        }
    }
}

void BD_draw_circle_highlighted(vec2 center, int radius, char to_put, char highlight)
{
    int max_index = center.x + radius + 1; // get the maxiumum radius of the square

    for (int i = center.x - radius; i < max_index; i ++) // begin counter center minus radius to get a full circle with the center as its center
    {
        for (int j = center.y - radius; j < max_index; j ++)
        {
            vec2 current_position = {i, j}; // get a vec of the current position
            if (V2_distf(center, current_position) < (float) radius) // if the distance is less than the radius draw it
            {
                move(j, i);
                addch(to_put);
            }
            else {
                move(j, i);
                addch(highlight);
            }
        }
    }
}

void BD_draw_point(char to_draw, int x, int y)
{
    move(y, x);
    addch(to_draw);
}

vec2 BD_V2_ind_on_square(vec2 center, int radius, int index)
{
    int max_index = center.x + radius;

    int ind = 0;

    for (int i = center.x; i < max_index; i ++) 
    {
        for (int j = center.y; j < max_index; j ++)
        {
            if (ind == index)
            {
                vec2 newvec = {i, j};
                return newvec;
            }
            ind ++;
        }
    }
}


vec2 BD_ind_on_square(int x, int y, int radius, int index)
{
    int max_index = x + radius;

    int ind = 0;

    for (int i = x; i < max_index; i ++) 
    {
        for (int j = y; j < max_index; j ++)
        {
            if (ind == index)
            {
                vec2 newvec = {i, j};
                return newvec;
            }
            ind ++;
        }
    }
}