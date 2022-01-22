#ifndef SIM
#define SIM 0

#include "particle.h"

#define falling_gravity 1.0f

//////////////////////////////////////:
// USER
//////////////////////////////////////:

// take in a particle list and update each in sequence
// note: makes no error checks as of yet
void SIM_update_P_list(P_ListElement *first);


//////////////////////////////////////:
// INTERNAL
//////////////////////////////////////:


// checks if the given x positions are within bounds
// note: simple if statement
BOOL in_bounds(int x, int y);

// takes in a particle and runs it through a switch case label to check what 
// type of update needs to be performed on it
// note: defaults to update_immobile()
void update_particle(P_ListElement *p, P_ListElement *first);

// takes a particle and checks first the spot directly below it, then to the left, then to the right,
// and if it can't find a free spot will remain immobile. Otherwise it will move to that spot
// note: makes use of P_list_position_occupied() function to check if the position is occupied
void update_falling(Particle *p, P_ListElement *first);

// keeps the particle immobile
void update_immobile(Particle *p, P_ListElement *first);

// update fire particle
void update_fire(P_ListElement *p, P_ListElement *first);

// general function to check the surrounding area of a position
// impl: bunch of if statements + P_list_position_occupied(x, y)
vec2 check_for_free_surrounding(P_ListElement *first, int x, int y);

// updates water particle
// impl: similar to falling particle only it also checks its left and right as well as down left and down
// right, and goes there if it can
void update_water(Particle *p, P_ListElement *first);

#endif