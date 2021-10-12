#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>

typedef enum {
	PLAYER_1 = 1,
	PLAYER_2 = 2
} Player;

typedef enum {
	INVALID_INDEX,
	USED_CELL
} Error;

void printBoard (char[3][3]);
int getValidIndex (const char *, const char[3][3]);
void handleError (Error);

int main (int argc, char* argv[])
{
	initscr ();
	cbreak ();

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
		mvprintw (15, max_x / 2 - 15, "Player %d", currentPlayer);
		index = getValidIndex ("Enter the Index: ", board);

		board[index / 3][index % 3 - 1] = mark;
		currentPlayer;
		//winState = checkWin ();
	} while (winState == -1);

	if (winState == 0) {
		printf ("It's a Draw!!\n");
	} else {
		printf ("Player %d won!\n", currentPlayer);
	}
	getch ();
	endwin ();

	return 0;
}

int getValidIndex (const char * prompt, const char board[3][3])
{
	int index;
	int max_x;
	int max_y;
	char buffer[50];

	getmaxyx (stdscr, max_y, max_x);

	while (1) {
		mvprintw (17, max_x / 2 - 15, "%s", prompt);
		move (18, max_x / 2 - 15);
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
	return index;
}

void printBoard (char board[3][3])
{
	int current_y = 10;
	int current_x = getmaxx (stdscr) / 2 - 5;

	for (int i = current_x; i < current_x + 8; i += 4) {
		mvvline (current_y - 1, i, ACS_VLINE, 5);
	}
	for (int i = current_y; i < current_y + 4; i += 2) {
		mvhline (i, current_x - 3, ACS_HLINE, 11);
	}

	//to get in position to print actual values
	current_y--;
	current_x -= 2; 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mvprintw (current_y + 2 * i, current_x + 4 * j, "%c", board[i][j]);
		}
	}
	move (current_y + 6, current_x);	//move cursor to just after the board
}

void handleError (Error errorCode)
{
	int max_y, max_x;
	int cur_x, cur_y;
	getmaxyx (stdscr, max_y, max_x);
	getyx (stdscr, cur_y, cur_x);

	move (20, max_x / 2 - 15);
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
