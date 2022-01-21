#include <ncurses.h>
#ifdef _WIN32
#include <Windows.h> // for windows sleep function
#else 
#include <unistd.h> // for sleep() function
#include <pthread.h> // for gameloop multithreading (intput etc...)
#endif

#include "basic_drawing.h"
#include "vec2.h"
#include "particle.h"
#include "simulation.h"

extern int max_height, max_width; // screen size dimensions

int main()
{

	initscr(); // initliaze the screen
	// raw(); // prevent cntrl+c quit

	start_color();

	P_create_colour_pairs();

	getmaxyx(stdscr, max_height, max_width); // get the screen size

	P_ListElement *list_first_ptr = P_init_list(P_new_ptr(air, 1, 0));

	for (int i = 0; i < max_width + 1; i ++)
	{
		P_list_add(list_first_ptr, P_new_ptr(bedrock, i, max_height - 1));
	}

	for(int i = 0; i < 50; i ++)
	{
		for (int j = 0; j < 10; j ++)
		{
			P_list_add(list_first_ptr, P_new_ptr(water, 1 + i, j));
		}
	} 

	for (int i = 0; i < 20; i ++)
	{
		P_list_add(list_first_ptr, P_new_ptr(wood, i + 1, 18));
	}

	P_list_draw(list_first_ptr);
	refresh();
	getch();

	while (1)
	{
		usleep(1000 * 50);
		refresh();
		erase();
		SIM_update_P_list(list_first_ptr);
		P_list_draw(list_first_ptr);
		// P_list_add(list_first_ptr, P_new_ptr(sand, max_width / 2, 10));
	}

	P_list_free(&list_first_ptr); // free particle list

	move (0, 0);

	getch(); // any key to quit
	endwin(); // free memory

	return 0; // return to end the program
}

