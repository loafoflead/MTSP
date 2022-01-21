#include "simulation.h"
#include "vec2.h"
#include "particle.h"

#include "main.h" // to use screen height and witdth variables (might change this to just use ncurses function idk)

#include <stddef.h>
#include <ncurses.h>

void SIM_update_P_list(P_ListElement *first)
{
    P_ListElement *temp = first;
    while(temp != NULL)
    {
        update_particle(temp, first);
        temp = temp->next_element;
    }
}

void update_particle(P_ListElement *p, P_ListElement *first)
{
    switch (p->current_element->type)
    {
        case sand:
            update_falling(p->current_element, first);
            break;
        
        case water:
            update_water(p->current_element, first);
            break;

        case wood:
            update_immobile(p->current_element, first);
            break;

        case fire:
            // update_falling(p->current_element, first);
            update_fire(p, first);
            break;

        default:
            update_immobile(p->current_element, first);
            break;
    }
}

void update_falling(Particle *p, P_ListElement *first)
{
    if (P_list_position_occupied(first, p->position.x, p->position.y + falling_gravity) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.y += falling_gravity;
    }
    else if (P_list_position_occupied(first, p->position.x - 1, p->position.y + falling_gravity) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.y += falling_gravity;
        p->position.x -= 1;
    }
    else if (P_list_position_occupied(first, p->position.x + 1, p->position.y + falling_gravity) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.y += falling_gravity;
        p->position.x += 1;
    }
}

void update_water(Particle *p, P_ListElement *first)
{
    if (P_list_position_occupied(first, p->position.x, p->position.y + falling_gravity) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.y += falling_gravity;
    }
    else if (P_list_position_occupied(first, p->position.x - 1, p->position.y + falling_gravity) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.y += falling_gravity;
        p->position.x -= 1;
    }
    else if (P_list_position_occupied(first, p->position.x + 1, p->position.y + falling_gravity) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.y += falling_gravity;
        p->position.x += 1;
    }
    else if (P_list_position_occupied(first, p->position.x - 1, p->position.y) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.x -= 1;
    }
    else if (P_list_position_occupied(first, p->position.x + 1, p->position.y) == FALSE && in_bounds(p->position.x, p->position.y))
    {
        p->position.x += 1;
    }
}

void update_fire(P_ListElement *p, P_ListElement *first)
{
    if (p->current_element->lifetime == 0)
    {
        P_list_delete(first, &p);
        return;
    }

    if (P_list_typeof_position(first, p->current_element->position.x, p->current_element->position.y + falling_gravity) == wood)
    {
        P_list_replacetypeat(first, p->current_element->position.x, p->current_element->position.y + falling_gravity, fire);
    }
    if (P_list_typeof_position(first, p->current_element->position.x - 1, p->current_element->position.y + falling_gravity) == wood)
    {
        P_list_replacetypeat(first, p->current_element->position.x - 1, p->current_element->position.y + falling_gravity, fire);
    }
    if (P_list_typeof_position(first, p->current_element->position.x + 1, p->current_element->position.y + falling_gravity) == wood)
    {
        P_list_replacetypeat(first, p->current_element->position.x + 1, p->current_element->position.y + falling_gravity, fire);
    }

    if (P_list_typeof_position(first, p->current_element->position.x - 1, p->current_element->position.y) == wood)
    {
        P_list_replacetypeat(first, p->current_element->position.x - 1, p->current_element->position.y, fire);
    }
    if (P_list_typeof_position(first, p->current_element->position.x + 1, p->current_element->position.y) == wood)
    {
        P_list_replacetypeat(first, p->current_element->position.x + 1, p->current_element->position.y, fire);
    }
    if (P_list_typeof_position(first, p->current_element->position.x - 1, p->current_element->position.y - 1) == wood)
    {
        P_list_replacetypeat(first, p->current_element->position.x - 1, p->current_element->position.y - 1, fire);
    }
    if (P_list_typeof_position(first, p->current_element->position.x + 1, p->current_element->position.y - 1) == wood)
    {
        P_list_replacetypeat(first, p->current_element->position.x + 1, p->current_element->position.y - 1, fire);
    }
    p->current_element->lifetime --;
}

BOOL in_bounds(int x, int y)
{
    if (x < max_width && x > -1 && y < max_height && y > -1){
        return TRUE;
    } else {
        return FALSE;
    }
}

void update_immobile(Particle *p, P_ListElement *first)
{

}