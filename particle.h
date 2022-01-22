#ifndef PARTICLE
#define PARTICLE 0

#include "vec2.h"
#include "type.h"

typedef enum particle_types 
{
    air,
    sand,
    wood,
    bedrock,
    fire,
    water,
} particle_types;

typedef struct
{
    vec2 position; 
    char display_character; // the display character (unneccessary?)
    particle_types type; // the type of the particle

    BOOL solid; // whether or not other particles can ovveride it
    int lifetime; // the number of turns after which it is destroyed, -1 if lives forever

} Particle;

typedef struct P_ListElement
{
    Particle* current_element;
    struct P_ListElement* prev_element;
    struct P_ListElement* next_element;
} P_ListElement;

////////////////////////////////////////////////////////////////:
// USER SIDE 
////////////////////////////////////////////////////////////////:

// create an array of a specific particle type
// NOTE: the particles are created in a circle around the initial position
Particle* P_new_array(particle_types type, vec2 center_position, int count); 

// create colour pairs for all particles
void P_create_colour_pairs();

// create a new particle of a given type with a given position
// NOTE: allocates a new variable and returns it
Particle P_new(particle_types type, int x, int y);

// same as previous but with vec2
Particle P_V2_new(particle_types type, vec2 position);

// create a new particle of given type with given position
// NOTE: uses malloc()
Particle *P_new_ptr(particle_types type, int x, int y);

// same as previous but using vec2
Particle *P_V2_new_ptr(particle_types type, vec2 pos);

// draws the particle to the screen at its position and using the character from its type
// note: makes use of ncurses mvaddch(char, y, x) function
void P_draw(Particle p);

// same function as above just uses a ptr instead of value
// note: if a null pointer is given, it returns
void P_draw_ptr(Particle *p);

// takes an array of particles and array length and draws them all
// note: makes use of the P_draw() function
void P_drawarr(Particle* p_array, int array_length);

////////////////:
// LISTS
////////////////:

// creates a new linked list of particles
// note: must take a malloc()'d particle ptr
P_ListElement* P_init_list(Particle *first);

// adds to a previously created linked list 
// note: particle given must be malloc()'d 
// note2: if a particles is added where another particle already exists, it uses the replacetypeat() func instead and free the pointer its given
P_ListElement* P_list_add(P_ListElement *first, Particle *to_add);

// deletes an element from the list
// note: uses free(), don't use this on an empty block of memory
void P_list_delete(P_ListElement *first, P_ListElement **el);

// frees a linked list (hopefully)
// note: uses free() function, this is why all ptrs to particles must be malloc()'d
int P_list_free(P_ListElement **first);

// gets the list of a linked list given the pointer to the first element in it
int P_list_len(P_ListElement *first);

// size in bytes of the particles in the linked list
// note: only counts the size of all the particles, ignores the linked list elements 
long int P_list_sizeof(P_ListElement *first);

// uses P_draw_ptr() function on all elements in a linked list
// note: will segfault if one element is corrupt
void P_list_draw(P_ListElement *first);

// replaces an element in the list at a given position with a particle of a different type
// note: deallocates memory of the particle in element->current_particle and reallocates a new variable using
// P_new_ptr() function
// returns: TRUE if a particle gets replaced | FALSE if no particle is found
P_ListElement *P_list_replacetypeat(P_ListElement *first, int x, int y, particle_types type);

// check if a position is occupied by an element in the list 
// note: runs through every element in the list comparing it to the position,
// if no resuts are found return false
BOOL P_list_position_occupied(P_ListElement *first, int x, int y);

// checks every element in the list against every other to check if there are any particles with the same position
// note: this function is pretty expensive (relatively ofc)
// impl: makes use of V2_cmp_ptr() (should be safe since we are using absolute variable, i just thought it would
// be a little faster to not copy the memory each time)
// + checks every item in list against every other
BOOL P_list_check_overlapping(P_ListElement *first);

// same as above function, only taking a vec2 as a position instead of x and y coord
BOOL P_V2_list_position_occupied(P_ListElement *first, vec2 pos);

// get the type of a particle at a given position
// note: returns particle_type.air when there are no particles at the given position
particle_types P_list_typeof_position(P_ListElement *first, int x, int y);

////////////////////////////////////////////////////////////////:
// INTERIOR MECHANICS 
////////////////////////////////////////////////////////////////:

// returns the appropriate character from the particle type given
// note: returns '?' if the character isn't known (maybe it should use the char in the struct but i might just remove)
char get_char_from_particle_type(particle_types type);

// get whether or not a particle is solid based on it's type
BOOL get_solidity(particle_types type);

// get the lifetime value of a particle based on it's type
int get_lifetime(particle_types type);

#endif