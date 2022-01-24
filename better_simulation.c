#include "vec2.h"
#include "particle.h"
#include "main.h"

#include "better_simulation.h"

#include <stddef.h>
#include <ncurses.h>
#include <stdlib.h>

void BSIM_update_list(P_ListElement *first)
{
    P_ListElement *temp = first;
    while(temp != NULL)
    {
        BSIM_update_particle(temp, first);
        temp = temp->next_element;
    }
}

void BSIM_update_particle(P_ListElement *first, P_ListElement *p)
{
    switch (p->current_element->type)
    {
        case sand:
            BSIM_update_falling(p->current_element, first);
            break;
        
        case water:
            BSIM_update_water(p->current_element, first);
            break;

        case wood:
            BSIM_update_immobile(p->current_element, first);
            break;

        case fire:
            // update_falling(p->current_element, first);
            BSIM_update_water(p->current_element, first);
            BSIM_update_fire(p, first);
            break;

        default:
            BSIM_update_immobile(p->current_element, first);
            break;
    }
}

BOOL in_bounds(int x, int y)
{
    if (x < max_width && x > -1 && y < max_height && y > -1){
        return TRUE;
    } else {
        return FALSE;
    }
}

vec2 BSIM_can_move(P_ListElement *first, vec2 pos, MoveVariants var, BOOL my_solidity)
{
    int x, y;
    x = pos.x;
    y = pos.y;
    switch (var)
    {
        case down_only:
            if (P_list_typeof_position(first, x, y + 1) == air && P_list_solidityof_position(first, x, y + 1) < my_solidity)
            {
                return V2_new(x, y + 1);
            }
            break;

        case downlr:
            if (P_list_typeof_position(first, x, y + 1) == air && P_list_solidityof_position(first, x, y + 1) < my_solidity)
            {
                return V2_new(x, y + 1);
            }
            else if (P_list_typeof_position(first, x + 1, y + 1) == air && P_list_solidityof_position(first, x + 1, y + 1) < my_solidity)
            {
                return V2_new(x + 1, y + 1);
            }
            else if (P_list_typeof_position(first, x - 1, y + 1) == air && P_list_solidityof_position(first, x - 1, y + 1) < my_solidity)
            {
                return V2_new(x - 1, y + 1);
            }
            break;

        case downlr_lr:
            if (P_list_typeof_position(first, x, y + 1) == air && P_list_solidityof_position(first, x, y + 1) < my_solidity)
            {
                return V2_new(x, y + 1);
            }
            else if (P_list_typeof_position(first, x + 1, y + 1) == air && P_list_solidityof_position(first, x + 1, y + 1) < my_solidity)
            {
                return V2_new(x + 1, y + 1);
            }
            else if (P_list_typeof_position(first, x - 1, y + 1) == air && P_list_solidityof_position(first, x - 1, y + 1) < my_solidity)
            {
                return V2_new(x - 1, y + 1);
            }
            else if (P_list_typeof_position(first, x + 1, y) == air && P_list_solidityof_position(first, x + 1, y) < my_solidity)
            {
                return V2_new(x + 1, y);
            }
            else if (P_list_typeof_position(first, x - 1, y) == air && P_list_solidityof_position(first, x - 1, y) < my_solidity)
            {
                return V2_new(x - 1, y);
            }
            break;

        case up_only:
            if (P_list_typeof_position(first, x, y - 1) == air && P_list_solidityof_position(first, x, y - 1) < my_solidity)
            {
                return V2_new(x, y - 1);
            }
            break;

        case uplr:
            if (P_list_typeof_position(first, x, y - 1) == air && P_list_solidityof_position(first, x, y - 1) < my_solidity)
            {
                return V2_new(x, y - 1);
            }
            else if (P_list_typeof_position(first, x + 1, y - 1) == air && P_list_solidityof_position(first, x + 1, y - 1) < my_solidity)
            {
                return V2_new(x + 1, y - 1);
            }
            else if (P_list_typeof_position(first, x - 1, y - 1) == air && P_list_solidityof_position(first, x - 1, y - 1) < my_solidity)
            {
                return V2_new(x - 1, y - 1);
            }
            break;

        case uplr_lr:
            if (P_list_typeof_position(first, x, y - 1) == air && P_list_solidityof_position(first, x, y - 1) < my_solidity)
            {
                return V2_new(x, y - 1);
            }
            else if (P_list_typeof_position(first, x + 1, y - 1) == air && P_list_solidityof_position(first, x + 1, y - 1) < my_solidity)
            {
                return V2_new(x + 1, y - 1);
            }
            else if (P_list_typeof_position(first, x - 1, y - 1) == air && P_list_solidityof_position(first, x - 1, y - 1) < my_solidity)
            {
                return V2_new(x - 1, y - 1);
            }
            else if (P_list_typeof_position(first, x + 1, y) == air && P_list_solidityof_position(first, x + 1, y) < my_solidity)
            {
                return V2_new(x + 1, y);
            }
            else if (P_list_typeof_position(first, x - 1, y) == air && P_list_solidityof_position(first, x - 1, y) < my_solidity)
            {
                return V2_new(x - 1, y);
            }
            break;

        case surround:
            if (P_list_typeof_position(first, x, y - 1) == air && P_list_solidityof_position(first, x, y - 1) < my_solidity)
            {
                return V2_new(x, y - 1);
            }
            else if (P_list_typeof_position(first, x + 1, y - 1) == air && P_list_solidityof_position(first, x + 1, y - 1) < my_solidity)
            {
                return V2_new(x + 1, y - 1);
            }
            else if (P_list_typeof_position(first, x - 1, y - 1) == air && P_list_solidityof_position(first, x - 1, y - 1) < my_solidity)
            {
                return V2_new(x - 1, y - 1);
            }
            else if (P_list_typeof_position(first, x + 1, y) == air && P_list_solidityof_position(first, x + 1, y) < my_solidity)
            {
                return V2_new(x + 1, y);
            }
            else if (P_list_typeof_position(first, x - 1, y) == air && P_list_solidityof_position(first, x - 1, y) < my_solidity)
            {
                return V2_new(x - 1, y);
            }
            else if (P_list_typeof_position(first, x - 1, y + 1) == air && P_list_solidityof_position(first, x - 1, y + 1) < my_solidity)
            {
                return V2_new(x - 1, y + 1);
            }
            else if (P_list_typeof_position(first, x + 1, y + 1) == air && P_list_solidityof_position(first, x + 1, y + 1) < my_solidity)
            {
                return V2_new(x + 1, y + 1);
            }
            else if (P_list_typeof_position(first, x, y + 1) == air && P_list_solidityof_position(first, x, y + 1) < my_solidity)
            {
                return V2_new(x, y + 1);
            }
            break;

        default:
            return V2_new(x, y);
    }
}

void BSIM_update_falling(Particle *p, P_ListElement *first)
{

}