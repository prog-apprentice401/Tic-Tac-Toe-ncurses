#include <ncurses.h>

#include "colorPairs.h"
#include "misc.h"

void handleError (Error errorCode)
{
	int max_y, max_x;
	int cur_x, cur_y;
	getmaxyx (stdscr, max_y, max_x);
	getyx (stdscr, cur_y, cur_x);

	move (MIN (max_y - 3, 10), max_x / 2 - 15);
	attron (COLOR_PAIR (RED_ON_BLACK) | A_BOLD);
	switch (errorCode) {
		case INVALID_INDEX:
			printw ("Invalid Index!");
			break;
		case USED_CELL:
			printw ("Cell is Used!");
			break;
		default:
			printw ("Unknown Error");
			break;
	}
	move (cur_y, cur_x);
}
