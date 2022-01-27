#include <ncurses.h>
#ifdef _WIN32
#include <Windows.h> // for windows sleep function
#else 
#include <unistd.h> // for sleep() function
#include <pthread.h> // for gameloop multithreading (intput etc...)
#define _OPEN_THREADS
#endif

#include <stdlib.h>
#include <stdio.h>

#include "basic_drawing.h"
#include "vec2.h"
#include "particle.h"
#include "simulation.h"
#include "better_simulation.h"
#include "input.h"

extern int max_height, max_width; // screen size dimensions

P_ListElement *list_first_ptr;

BOOL run = TRUE;

void* draw(void* arg)
{ 
	while (run == TRUE)
	{
		move(max_height, max_width - 5);
		printw("p:%d", P_list_len(list_first_ptr));
		usleep(1000 * 50);
		refresh();
		erase();
		BSIM_update_P_list(list_first_ptr);
		P_list_draw(list_first_ptr);
		P_list_add(list_first_ptr, P_new_ptr(water, 40, 0));
		P_list_remove_out_of_bounds(list_first_ptr);
	}
}

int main()
{

	initscr(); // initliaze the screen
	noecho();  // dont print what the user types
	cbreak(); // prevent linefeed?
	// raw(); // prevent cntrl+c quit
	
	if (curs_set(0) == ERR)
	{
		printw("[NON FATAL] Error setting the cursor invisible");
	}

	mousemask(  ALL_MOUSE_EVENTS, NULL);
	keypad(stdscr, TRUE); // magically makes the mouse input work :)

	MEVENT event;
	pthread_t draw_thread;

	

	start_color();

	P_create_colour_pairs();

	getmaxyx(stdscr, max_height, max_width); // get the screen size

	list_first_ptr = P_init_list(P_new_ptr(air, -1, -1));

	INP_new(wood, square, 8);

	for (int i = 0; i < max_width + 1; i ++)
	{
		P_list_add(list_first_ptr, P_new_ptr(bedrock, i, max_height - 1));
	}

	// for(int i = 0; i < 50; i ++)
	// {
	// 	for (int j = 0; j < 10; j ++)
	// 	{
	// 		P_list_add(list_first_ptr, P_new_ptr(wood, 1 + i, j));
	// 	}
	// } 

	// for (int i = 0; i < 20; i ++)
	// {
	// 	P_list_add(list_first_ptr, P_new_ptr(wood, i + 1, 18));
	// }

	// P_list_replacetypeat(list_first_ptr, 20, 5, fire);

	P_list_draw(list_first_ptr);
	refresh();
	getch();

	if (pthread_create(&draw_thread, NULL, draw, "drawing_thread") != 0)
	{
		printw("rendering thread creation error");
		exit(1);
	}

	while (run == TRUE)
	{
		
		int ch = wgetch(stdscr);
		if (ch == KEY_MOUSE)
		{
			// printw("h");
			if (getmouse(&event) == OK)
			{
				if (event.bstate & BUTTON1_CLICKED)
				{
					INP_handle_leftclick(list_first_ptr, event.x, event.y);
				}
			}
		}
		else {
			INP_handle_key(list_first_ptr, ch);
		}
	}

	P_list_free(&list_first_ptr); // free particle list

	move (0, 0);
	
	curs_set(1);

	getch(); // any key to quit
	endwin(); // free memory

	return 0; // return to end the program
}

