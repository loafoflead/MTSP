#include "particle.h"
#include "vec2.h"
#include "basic_drawing.h"

#include "type.h"

#include <ncurses.h>
#include <stdlib.h>

P_ListElement* P_init_list(Particle *first)
{
    P_ListElement *new_element = (P_ListElement*) malloc(sizeof(P_ListElement));
    new_element->current_element = first;
    new_element->prev_element = new_element;
    new_element->next_element = NULL;
}

P_ListElement *P_list_add(P_ListElement *first, Particle *to_add)
{
    if (P_V2_list_position_occupied(first, to_add->position)) // if the position is occupied, simply replace it with the new type
    {
        int x, y;
        particle_types type;
        x = to_add->position.x;
        y = to_add->position.y;
        type = to_add->type;
        free(to_add);
        return P_list_replacetypeat(first, x, y, type);
    }
    P_ListElement *next = first; // get the next element in the list
    while (next->next_element != NULL)
    {
        next = next->next_element; // increment in the list until the next element in the list is empty
    }
    P_ListElement *new_element =(P_ListElement* ) malloc(sizeof(P_ListElement)); // create a new list element
    new_element->current_element = to_add;
    new_element->next_element = NULL; // assign vars
    new_element->prev_element = next;
    next->next_element = new_element; // add a ref to the new element to the list
    return new_element;
}

BOOL P_list_check_overlapping(P_ListElement *first)
{
    P_ListElement *temp1 = first;
    while (temp1 != NULL)
    {
        P_ListElement *temp2 = first;
        while (temp2 != NULL)
        {
            if (V2_cmp_ptr(&temp1->current_element->position, &temp2->current_element->position) && temp1 != temp2)
            {
                return TRUE;
            }
            temp2 = temp2->next_element;
        }
        temp1 = temp1 -> next_element;
    }
    return FALSE;
}

int P_list_free(P_ListElement **firs)
{
    P_ListElement *first = *firs;
    int freed = 0;
    while (first != NULL)
    {
        P_ListElement* temp = first;
        first = first -> next_element;
        free(temp -> current_element);
        free(temp);
        freed ++;
    }
    *firs = NULL;
    return freed;
}

int P_list_len(P_ListElement *first)
{
    if (first == NULL)
    {
        return -1;
    }
    P_ListElement *next = first; // pointer to the 1st list element
    int countr = 0;
    while (next != NULL) // iterate thru list incrementing counter as you do 
    {
        next = next->next_element;
        countr ++;
    }
    return countr; // return count
}

long int P_list_sizeof(P_ListElement *first)
{
    long int total_size = 0;
    P_ListElement* temp = first;
    while (temp != NULL)
    {
        total_size += sizeof(temp->current_element);
        temp = temp->next_element;
    }
    return total_size;
}

void P_list_draw(P_ListElement *first)
{
    P_ListElement *next = first;
    int count = 0;
    while(next->next_element != NULL)
    {
        count ++;
        P_draw_ptr(next->current_element);
        next = next->next_element;
    }
    P_draw_ptr(next->current_element);
}

BOOL P_list_position_occupied(P_ListElement *first, int x, int y)
{
    P_ListElement *temp = first;
    while(temp != NULL)
    {
        if (temp->current_element->position.x == x && temp->current_element->position.y == y)
        {
            return TRUE;
        }
        temp = temp->next_element;
    }
    return FALSE;
}

BOOL P_V2_list_position_occupied(P_ListElement *first, vec2 pos)
{
    P_ListElement *temp = first;
    while(temp != NULL)
    {
        if (temp->current_element->position.x == pos.x && temp->current_element->position.y == pos.y)
        {
            return TRUE;
        }
        temp = temp->next_element;
    }
    return FALSE;
}

particle_types P_list_typeof_position(P_ListElement *first, int x, int y)
{
    P_ListElement *temp = first;
    while(temp != NULL)
    {
        if (temp->current_element->position.x == x && temp->current_element->position.y == y)
        {
            return temp->current_element->type;
        }
        temp = temp->next_element;
    }
    return air;
}

P_ListElement *P_list_replacetypeat(P_ListElement *first, int x, int y, particle_types type)
{
    P_ListElement *temp = first;
    while(temp != NULL)
    {
        if (temp->current_element->position.x == x && temp->current_element->position.y == y)
        {
            free(temp->current_element);
            temp->current_element = P_new_ptr(type, x, y);
            return temp;
        }
        temp = temp->next_element;
    }
    return NULL;
}

void P_list_delete(P_ListElement *first, P_ListElement **el)
{
    if (el == NULL)
    {
        return;
    }

    P_ListElement *temp = first;
    while(temp != NULL)
    {
        if (temp->next_element == *el)
        {
            P_ListElement *element = *el;
            temp->next_element = element->next_element;
            free(*el);
            *el = NULL;
            return;
        }
        temp = temp->next_element;
    }
}

Particle P_new(particle_types type, int x, int y)
{
    vec2 position = {x, y};
    Particle new_pt = {position, '?', type, get_solidity(type), get_lifetime(type)};
    return new_pt;
}

Particle P_V2_new(particle_types type, vec2 position)
{
    Particle new_pt = {position, '?', type, get_solidity(type), get_lifetime(type)};
    return new_pt;
}

Particle *P_new_ptr(particle_types type, int x, int y)
{
    vec2 position = {x, y};
    Particle *new_pt_ptr = (Particle*) malloc(sizeof(Particle));
    new_pt_ptr->position = position;
    new_pt_ptr->solid = get_solidity(type);
    new_pt_ptr->lifetime = get_lifetime(type);
    new_pt_ptr->type = type;
    return new_pt_ptr;
}

Particle *P_V2_new_ptr(particle_types type, vec2 pos)
{
    Particle *new_pt_ptr = (Particle*) malloc(sizeof(Particle));
    new_pt_ptr->position = pos;
    new_pt_ptr->type = type;
    new_pt_ptr->solid = get_solidity(type);
    new_pt_ptr->lifetime = get_lifetime(type);
    return new_pt_ptr;
}

int get_lifetime(particle_types type)
{
    switch (type)
    {
        case wood:
        case sand:
        case bedrock:
        case air:
        case water:
            return -1;

        case fire:
            return 20;

        default:
            return -1;
    }
}

BOOL get_solidity(particle_types type)
{
    switch(type)
    {
        case sand:
        case wood:
        case bedrock:
        case water:
            return TRUE;

        case fire:
        case air:
            return FALSE;

        default:
            return TRUE;
    }
}

char get_char_from_particle_type(particle_types type)
{
    switch(type)
    {
        case sand:
            return 's';

        case wood:
            return 'w';

        case bedrock:
            return 'B';

        case fire:
            return 'F';

        case water:
            return 'W';

        case air:
            return 'A';

        default:
            return '?'; // this should only happen when given a null type
    }
}

int get_pair_from_p_type(particle_types type)
{
    switch(type)
    {
        case water:
            return 1;

        case sand:
            return 2;

        case fire:
            return 3;

        case wood:
            return 4;
        
        case bedrock:
            return 5;

        default:
            return 0;
    }
}

void P_create_colour_pairs()
{
    init_pair(1, COLOR_BLUE, COLOR_BLUE); // water colour
    init_pair(2, COLOR_YELLOW, COLOR_YELLOW); // sand
    init_pair(3, COLOR_RED, COLOR_RED); // fire
    init_pair(4, COLOR_WHITE, COLOR_BLACK); // wood
    init_pair(5, COLOR_BLACK, COLOR_WHITE); // bedrock
}

void P_draw(Particle p)
{
    attron(COLOR_PAIR(get_pair_from_p_type(p.type)));
    BD_draw_point(get_char_from_particle_type(p.type), p.position.x, p.position.y); 
    attroff(COLOR_PAIR(get_pair_from_p_type(p.type)));
}

void P_draw_ptr(Particle *p)
{
    if (p == NULL)
    {
        return;
    }
    attron(COLOR_PAIR(get_pair_from_p_type(p->type)));
    BD_draw_point(get_char_from_particle_type(p->type), p->position.x, p->position.y);
    attroff(COLOR_PAIR(get_pair_from_p_type(p->type)));
}

void P_drawarr(Particle* p_array, int array_length)
{
    for (int i = 0; i < array_length - 1; i ++)
    {
        P_draw(p_array[i]);
    }
}
