#ifndef INPUT
#define INPUT 

typedef enum 
{
    point,
    square,
} SpawningVariants; // the configuration in which particles are spawned by the player

#include "particle.h"

//////////////////////////////:
// USER
//////////////////////////////:

// decides what to do with a click on a given position
// calls P_list_add() when configuration is 'point' 
// defaults to just adding 
void INP_handle_leftclick(P_ListElement *first, int x, int y);

// sets up the variables
// note: defaults to sand in a point configuration with a radius of one
void INP_setup();

// constructor for input class
// note: do not use this as well as INP_setup() unless you want some unpredictable behaviour
void INP_new(particle_types type, SpawningVariants variant, int radius);

// getters and setter
void INP_set_spawn_radius(int newrad);
void INP_set_spawn_type(particle_types type);
void INP_set_spawn_variant(SpawningVariants var);

//////////////////////////////;
// INTERNAL
//////////////////////////////;

// inserts into the given list an amount of particle arranged in a square based on the selected radius
// note: uses P_list_add() and P_new_ptr()
void spawn_square(P_ListElement *first, int x, int y);

#endif