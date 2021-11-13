#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>

#include "win.h"
#include "misc.h"
#include "colorPairs.h"


void printBoard (char[3][3]);
int getValidIndex (const char *, const char[3][3]);

int main (int argc, char* argv[])
{
	initscr ();
	cbreak ();
	start_color ();

	initColorPairs ();	//from colorPairs.h

	char board[3][3] = {
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'}
	};
	int index = 0;
	int max_x, max_y;
	int winState = -1;
	Player currentPlayer = PLAYER_2;
	char mark;

	getmaxyx (stdscr, max_y, max_x);

	do {
		printBoard (board);
		clrtobot ();
		refresh ();

		currentPlayer = (currentPlayer % 2) ? 2 : 1;
		mark = (currentPlayer == PLAYER_1) ? 'X' : 'O';
		attron (COLOR_PAIR (BLUE_ON_BLACK) | A_BOLD);
		mvprintw (MIN (max_y - 5, 8), max_x / 2 - 15, "Player %d", currentPlayer);
		index = getValidIndex ("Enter the Index: ", board);

		board[index / 3][index % 3 - 1] = mark;
		winState = checkWin (board, currentPlayer);
	} while (winState == -1);

	printBoard (board);
	clrtobot ();
	refresh ();
	
	attron (COLOR_PAIR (YELLOW_ON_BLACK) | A_BOLD);
	if (winState == 0) {
		mvprintw (MIN (max_y - 4, 8), max_x / 2 - 15, "It's a Draw!!\n");
	} else {
		mvprintw (MIN (max_y - 4, 8), max_x / 2 - 15, "Player %d won!\n", currentPlayer);
	}
	standend ();
	getch ();
	endwin ();

	return winState;
}

int getValidIndex (const char * prompt, const char board[3][3])
{
	int index;
	int max_x;
	int max_y;
	char buffer[50];

	getmaxyx (stdscr, max_y, max_x);

	while (1) {
		attron (COLOR_PAIR (YELLOW_ON_BLACK));
		mvprintw (MIN (max_y - 2, 12), max_x / 2 - 15, "%s", prompt);
		move (MIN (max_y - 1, 13), max_x / 2 - 15);
		clrtobot();
		getnstr (buffer, 40);
		index = atoi (buffer);

		if (index < 1 || index > 9) {
			handleError (INVALID_INDEX);
		} else if (isalpha (board[index / 3][index % 3 - 1])) {
			handleError (USED_CELL);
		} else {
			break;
		}
	}
	standend ();
	return index;
}

void printBoard (char board[3][3])
{
	//according to value printing, not border
	int current_y = 1;
	int current_x = getmaxx (stdscr) / 2 - 4;

	attron (COLOR_PAIR (GREEN_ON_BLACK) | A_BOLD);
	for (int i = 0; i < 2; i++) {
		//the wierd value jumps 4 columns for each vertical line
		mvvline (current_y, current_x + 2 + 4 * i, ACS_VLINE, 5);
	}
	for (int i = 0; i < 2; i++) {
		//wierd y value skips 2 rows for each horizontal line
		mvhline (current_y + 1 + 2 * i, current_x - 1, ACS_HLINE, 11);
	}

	mvaddch (current_y + 1, current_x + 2, ACS_PLUS | A_BOLD);
	mvaddch (current_y + 1, current_x + 6, ACS_PLUS | A_BOLD);
	mvaddch (current_y + 3, current_x + 2, ACS_PLUS | A_BOLD);
	mvaddch (current_y + 3, current_x + 6, ACS_PLUS | A_BOLD);

	//to get in position to print actual values
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!isalpha (board[i][j])) {	//empty cell
				attron (A_DIM);
			}
			mvprintw (current_y + 2 * i, current_x + 4 * j, "%c", board[i][j]);
			attroff (A_DIM);
		}
	}
	move (current_y + 6, current_x);	//move cursor to just after the board
	standend ();
}

