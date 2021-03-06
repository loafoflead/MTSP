#include "particle.h"
#include "input.h"
// #include "main.h"

#include <ncurses.h>

static particle_types selected_type;
static SpawningVariants selected_spawn_variant;

static int spawn_radius = 0;

void INP_setup()
{
    selected_type = sand;
    selected_spawn_variant = point;
    spawn_radius = 1;
}

void INP_new(particle_types type, SpawningVariants variant, int radius)
{
    selected_type = type;
    selected_spawn_variant = variant;
    spawn_radius = radius;
}

void INP_set_spawn_radius(int newrad)
{
    spawn_radius = newrad;
}

void INP_set_spawn_type(particle_types type)
{
    selected_type = type;
}

void INP_set_spawn_variant(SpawningVariants var)
{
    selected_spawn_variant = var;
}

void INP_handle_leftclick(P_ListElement *first, int x, int y)
{
	switch (selected_spawn_variant)
    {
        case point:
            P_list_add(first, P_new_ptr(selected_type, x, y));
            break;

        case square:
            spawn_square(first, x, y);
            break;

        default:
            P_list_add(first, P_new_ptr(selected_type, x, y));
            break;
    }
}

void INP_handle_key(P_ListElement *first, char ch)
{
    switch (ch)
    {
        case 's':
            INP_set_spawn_type(sand);
            break;

        case 'f':
            INP_set_spawn_type(fire);
            break;
        
        case 'w':
            INP_set_spawn_type(water);
            break;
            
        case 'o':
			INP_set_spawn_type(wood);
			break;

        case 'p':
            INP_set_spawn_variant(point);
            break;

        case 'r':
            INP_set_spawn_variant(square);
            break;

        case 'c':
    		if (P_list_check_overlapping(first))
            {
                P_ListElement *ptr;
                printw("%d", ptr->current_element->position);
            }
            break;

        default:
            break;
    }
}

void spawn_square(P_ListElement *first, int x, int y)
{
    int xmax_index = x + spawn_radius + 1;
    int ymax_index = y + spawn_radius + 1;

    for (int i = y - spawn_radius; i < ymax_index; i ++) // begin counter center minus radius to get a full circle with the center as its center
    {
        for (int j = x - spawn_radius; j < xmax_index; j ++)
        {
            P_list_add(first, P_new_ptr(selected_type, j, i));
        }
    }
}
