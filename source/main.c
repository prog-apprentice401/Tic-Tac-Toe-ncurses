#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>

#include "win.h"
#include "misc.h"
#include "colorPairs.h"


void printBoard (char *, int);
void getValidIndex (const char *, int, int *, int *);

int main (int argc, char* argv[])
{
	if (argc != 2) {
		fputs ("Usage: tictactoe <sideLength>\n", stderr);
		return 1;
	}
	int sideLength = atoi (argv[1]);
	if (sideLength < 3 || sideLength > 26) {
		fputs ("Sidelength should be between 3 and 26 (inclusive range)\n", stderr);
		return 1;
	}
	initscr ();
	cbreak ();
	start_color ();

	initColorPairs ();	//from colorPairs.h

	int max_x, max_y;
	int winState = -1;
	int enteredRow;
	int enteredCol;

	Player currentPlayer = PLAYER_2;
	char mark;
	char board[sideLength][sideLength];

	getmaxyx (stdscr, max_y, max_x);
	if (2 * sideLength + 8 > max_y || 4 * sideLength + 3 > max_x) {
		printw ("Screen is too small for the specified board size\n"
		        "Press any key to exit");
		getch ();
		endwin ();
		return -1;
	}
	for (int i = 0; i < sideLength; i++) {
		for (int j = 0; j < sideLength; j++) {
			board [i][j] = ' ';
		}
	}

	do {
		printBoard ((char *) board, sideLength);
		clrtobot ();
		refresh ();

		currentPlayer = (currentPlayer % 2) ? 2 : 1;
		mark = (currentPlayer == PLAYER_1) ? 'X' : 'O';
		attron (COLOR_PAIR (BLUE_ON_BLACK) | A_BOLD);
		mvprintw (2 * sideLength + 2, max_x / 2 - 2 * sideLength, "Player %d", currentPlayer);
		getValidIndex ((char *) board, sideLength, &enteredRow, &enteredCol);

		board[enteredRow][enteredCol] = mark;
		winState = checkWin (board, currentPlayer);
	} while (winState == -1);

	printBoard ((char *) board, sideLength);
	clrtobot ();
	refresh ();
	
	attron (COLOR_PAIR (YELLOW_ON_BLACK) | A_BOLD);
	if (winState == 0) {
		mvprintw (max_y - 4, max_x / 2 - 2 * sideLength, "It's a Draw!!\n");
	} else {
		mvprintw (max_y - 4, max_x / 2 - 2 * sideLength, "Player %d won!\n", currentPlayer);
	}
	standend ();
	getch ();
	endwin ();

	return 0;
}

void getValidIndex (const char* board, int sideLength, int *enteredRow, int * enteredCol)
{
	int max_x;
	int max_y;
	char buffer[50];

	getmaxyx (stdscr, max_y, max_x);

	while (1) {
		attron (COLOR_PAIR (YELLOW_ON_BLACK));
		mvprintw (max_y - 3, max_x / 2 - 2 * sideLength, "Enter the Index: ");
		move (max_y - 2, max_x / 2 - 2 * sideLength);
		getnstr (buffer, 40);
		
		*enteredCol = toupper (buffer[0]) - 'A';	//get the first character as row letter
		*enteredRow = atoi (buffer + 1) - 1;	//indexing on screen starts from 1

		if (*enteredRow < 0 || *enteredRow >= sideLength
		    || *enteredCol < 0 || *enteredCol >= sideLength) {
			handleError (INVALID_INDEX);
		} else if (!isspace (board[*enteredRow * sideLength + *enteredCol])) {
			handleError (USED_CELL);
		} else {
			break;
		}
	}
	standend ();
}

void printBoard (char *board, int sideLength)
{
	//according to value printing, not border
	int current_y = 2;
	int current_x = getmaxx (stdscr) / 2 - 2 * sideLength + 1;

	attron (COLOR_PAIR (GREEN_ON_BLACK) | A_BOLD);
	for (int i = 0; i < sideLength - 1; i++) {
		mvaddch (current_y - 1, current_x + 4 * i, (i + 'A') | A_DIM);
		mvvline (current_y, current_x + 4 * i + 2, ACS_VLINE, 2 * sideLength - 1);
	}
	//print the last remaining column index
	mvaddch (current_y - 1, current_x + 4 * (sideLength - 1), (sideLength + 'A' - 1) | A_DIM);
	for (int i = 0; i < sideLength - 1; i++) {
		mvaddch (current_y + 2 * i, current_x - 2, (i + '1') | A_DIM);
		mvhline (current_y + 2 * i + 1, current_x - 1, ACS_HLINE, 4 * sideLength - 1);
	}
	//print last remaining row index
	mvaddch (current_y + 2 * sideLength - 2, current_x - 2, (sideLength + '0') | A_DIM);
	/*
	mvaddch (current_y + 1, current_x + 2, ACS_PLUS | A_BOLD);
	mvaddch (current_y + 1, current_x + 6, ACS_PLUS | A_BOLD);
	mvaddch (current_y + 3, current_x + 2, ACS_PLUS | A_BOLD);
	mvaddch (current_y + 3, current_x + 6, ACS_PLUS | A_BOLD);
	*/

	//printing actual values
	for (int i = 0; i < sideLength; i++) {
		for (int j = 0; j < sideLength; j++) {
			mvprintw (current_y + 2 * i, current_x + 4 * j, "%c", board[i * sideLength + j]);
		}
	}
	move (current_y + 2 * sideLength - 1, current_x);	//move cursor to just after the board
	standend ();
}

