#include <ncurses.h>
#include "colorPairs.h"

void initColorPairs ()
{
	init_pair (BLACK_ON_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair (RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair (GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair (YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
	init_pair (BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
	init_pair (MAGENTA_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK);
	init_pair (CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair (WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
}
