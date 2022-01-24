#ifndef BSIM
#define BSIM

#include "vec2.h"
#include "particle.h"

#define gravity 0.5f

typedef enum
{
    down_only, // can only move one space down
    downlr, // down + down left + down right
    downlr_lr, // down + down left + left + down right + right
    surround, // all adjacent spaces
    up_only, // only space up
    uplr, // up + up left + up right
    uplr_lr, // up + up left + left + up right + right
} MoveVariants;

// update a list of P_element's, looping through each element and updating each
// particle one by one
void BSIM_update_P_list(P_ListElement *first);

// check if a particle is in bounds
// note: makes use of "main.h"s height and width vars
BOOL BSIM_in_bounds(int x, int y);

// update a particle
// impl: switch case statement that expands into the functions used
void BSIM_update_particle(P_ListElement *first, P_ListElement *p);

// update a falling particle
void BSIM_update_falling(Particle *p, P_ListElement *first);

// update a fire particle
void BSIM_update_fire(P_ListElement *p, P_ListElement *first);

// update an immobile particle
void BSIM_update_immobile(Particle *p, P_ListElement *first);

// update a water particle
void BSIM_update_water(Particle *p, P_ListElement *first);

// take a center position and check the positions around it in the given configuration and either checking 
// or ignoring solidity. 
// note: if no free spot if found will return the origin point
vec2 BSIM_can_move(P_ListElement *first, vec2 pos, MoveVariants var, BOOL my_solidity);

// check if a position is valid for a given solidity
BOOL V2_can_move(P_ListElement *first, vec2 pos, BOOL solidity);

// check if an xy coordinate is valid for a given solidity
BOOL can_move(P_ListElement *first, int x, int y, BOOL solidity);

#endif
