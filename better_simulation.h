#ifndef BSIM
#define BSIM

#include "vec2.h"
#include "particle.h"

typedef enum
{
    down_only, // can only move one space down
    downlr, // down + down left + down right
    downlr_lr, // down + down left + left + down right + right
    surround, // all adjacent spaces
    up_only, // only space up
    uplr, // up + up left + up right
    uplr_lr, // up + up left + left + up right + right
} MoveVariants

// check if a particle is in bounds
// note: makes use of "main.h"s height and width vars
BOOL in_bounds(int x, int y);

// update a falling particle
void BSIM_update_falling(Particle *p, P_ListElement *first);

// take a center position and check the positions around it in the given configuration and either checking 
// or ignoring solidity. 
// note: if no free spot if found will return the origin point
vec2 BSIM_can_move(P_ListElement *first, vec2 pos, MoveVariants var, BOOL my_solidity);

#endif