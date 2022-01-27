#include "vec2.h"
#include "particle.h"
#include "main.h"

#include "better_simulation.h"

#include <stddef.h>
#include <ncurses.h>
#include <stdlib.h>

void BSIM_update_P_list(P_ListElement *first)
{
    P_ListElement *temp = first;
    while(temp != NULL)
    {
        BSIM_update_particle(first, temp);
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
            BSIM_update_falling(p->current_element, first);
            //BSIM_update_water(p->current_element, first);
            BSIM_update_fire(p, first);
            break;

        default:
            BSIM_update_immobile(p->current_element, first);
            break;
    }
}

BOOL BSIM_in_bounds(int x, int y)
{
    if (x < max_width && x > -1 && y < max_height && y > -1){
        return TRUE;
    } else {
        return FALSE;
    }
}

vec2 BSIM_can_move(P_ListElement *first, vec2 pos, MoveVariants var, int my_solidity)
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

void BSIM_update_water(Particle *p, P_ListElement *first)
{
    p->velocity = V2F_add(p->velocity, V2F_new(0, gravity)); // accelerate with gravity 
    vec2f next_position = V2F_add(V2F_fromv2(p->position), p->velocity); // get the position of the particle plus its velocity

    int xNew, yNew;
    V2_store(V2_fromf(next_position), &xNew, &yNew); // values for ease of use

    vec2 updated_position = p->position; // the position the particle is gonna end up at

    // note: i cant fucking beleive this code block works lmao
    for ( 
        int x = p->position.x, y = p->position.y; // get x and y variables
        x != xNew, y != yNew; // while neither of them are equal to their respective new positions
        (x < xNew) ? x ++ : x --, // increment x appropriately with its value
        (y < yNew) ? y ++ : y -- // increment y appropriately with its value
    ) // iterate along the new position 
    {
        updated_position.x = x;
        updated_position.y = y; // get next position

        if (V2_can_move(first, updated_position, p->solid)) // straight down
        {
            continue;
        }
        else if (V2_can_move(first, V2_add(updated_position, V2_new(1, 0)), p->solid)) // to the right-down
        {
            xNew ++; // go another square to the left
            continue;
        }
        else if (V2_can_move(first, V2_add(updated_position, V2_new(-1, 0)), p->solid)) // to the left-down
        {
            xNew --; // go another square to the left
            continue;
        }
        else if (V2_can_move(first, V2_add(updated_position, V2_new(-1, -1)), p->solid)) // to the left
        {
            xNew --; // go another square to the left
            yNew --;
            y --; // also have to decrement y
            continue;
        }
        else if (V2_can_move(first, V2_add(updated_position, V2_new(1, -1)), p->solid)) // to the right
        {
            xNew ++; // go another square to the left
            yNew --;
            y --; // also have to decrement y
            continue;
        }
        else { // no free spots
            updated_position.x --;
            updated_position.y --; // go back a spot (tbs) ((to be safe))
            break;
        }
    }
    p->position = updated_position; // put the particle in the new pos
}

void BSIM_update_immobile(Particle *p, P_ListElement *first)
{
	
}

void BSIM_update_fire(P_ListElement *p, P_ListElement *first)
{
	if (p->current_element->lifetime == 0)
    {
        P_list_delete(first, &p);
        return;
    }
    
    int falling_gravity = 1;

    for (int i = 0; i < rand() % 4; i ++)
    {
        switch (rand() % 20)
        {
            case 0:
                if (P_list_typeof_position(first, p->current_element->position.x, p->current_element->position.y + falling_gravity) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x, p->current_element->position.y + falling_gravity, fire);
                }
                break;

            case 1:
                if (P_list_typeof_position(first, p->current_element->position.x - 1, p->current_element->position.y + falling_gravity) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x - 1, p->current_element->position.y + falling_gravity, fire);
                }
                break;

            case 2:
                if (P_list_typeof_position(first, p->current_element->position.x + 1, p->current_element->position.y + falling_gravity) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x + 1, p->current_element->position.y + falling_gravity, fire);
                }
                break;

            case 3:
                if (P_list_typeof_position(first, p->current_element->position.x - 1, p->current_element->position.y) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x - 1, p->current_element->position.y, fire);
                }
                break;

            case 4:
                if (P_list_typeof_position(first, p->current_element->position.x + 1, p->current_element->position.y) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x + 1, p->current_element->position.y, fire);
                }
                break;

            case 5:
                if (P_list_typeof_position(first, p->current_element->position.x - 1, p->current_element->position.y - 1) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x - 1, p->current_element->position.y - 1, fire);
                }
                break;

            case 6:
                if (P_list_typeof_position(first, p->current_element->position.x + 1, p->current_element->position.y - 1) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x + 1, p->current_element->position.y - 1, fire);
                }
                break;

            case 7:
                if (P_list_typeof_position(first, p->current_element->position.x, p->current_element->position.y - 1) == wood)
                {
                    P_list_replacetypeat(first, p->current_element->position.x, p->current_element->position.y - 1, fire);
                }
                break;

            default:
                break;
        }
    }
 
    p->current_element->lifetime --;
}

void BSIM_update_falling(Particle *p, P_ListElement *first)
{
	p->velocity = V2F_add(p->velocity, V2F_new(0, gravity)); // change the velocity of the particle
	vec2f new_position = V2F_add(p->velocity, V2F_fromv2(p->position)); // calculate new position
	vec2 next_position = V2_fromf(new_position); // get the next grid aligned position
	int solidity = p->solid; // the solidity of the particle
	for (int i = p->position.y; i < next_position.y; i ++)
	{
		vec2 next_pos = V2_add(p->position, V2_new(0, 1));
		if (V2_can_move(first, next_pos, solidity))
		{
			p->position.y ++;
		}
		else if (V2_can_move(first, V2_add(next_pos, V2_new(1, 0)), solidity))
		{
			p->position.y ++;
			p->position.x ++;
		}
		else if (V2_can_move(first, V2_add(next_pos, V2_new(-1, 0)), solidity))
		{
			p->position.y ++;
			p->position.x --;
		}
		else {
			p->velocity = V2F_zero();
			break;
		}
	}
}

BOOL V2_can_move(P_ListElement *first, vec2 pos, int solidity)
{
	if (P_list_typeof_position(first, pos.x, pos.y) == air && P_list_solidityof_position(first, pos.x, pos.y) < solidity)
	{
		return TRUE; // true if position is air and solidity is inferior to existing position
	}
	return FALSE;
}

BOOL can_move(P_ListElement *first, int x, int y, int solidity)
{
	if (P_list_typeof_position(first, x, y) == air && P_list_solidityof_position(first, x, y) < solidity)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}
