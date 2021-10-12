#include <stdio.h>
#include <ncurses.h>

typedef enum {
	PLAYER_1 = 1,
	PLAYER_2 = 2
} Player;

void printBoard (char[3][3]);
int getIndex (const char *, const char *);

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
	int winState = -1;
	Player currentPlayer = PLAYER_2;
	char mark;

	do {
		clear ();
		printBoard (board);
		refresh ();

		currentPlayer = (currentPlayer % 2) ? 2 : 1;
		mark = (currentPlayer == PLAYER_1) ? 'X' : '0';
		mvprintw (6, 0, "Player %d", currentPlayer);
		index = getIndex ("Enter the Index:  ", "Invalid Index!! Try Again");
		
		board[index / 3][index % 3 - 1] = mark;
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

void printBoard (char board[3][3])
{
	int current_y = 1;
	for (int i = 0; i < 2; i++, current_y += 2) {
		mvhline (current_y, 0, ACS_HLINE, 11);
	}
	int current_x = 3;
	for (int i = 0; i < 2; i++, current_x += 4) {
		mvvline (0, current_x, ACS_VLINE, 5);
	}
	mvaddch (1, 3, ACS_PLUS);
	mvaddch (1, 7, ACS_PLUS);
	mvaddch (3, 3, ACS_PLUS);
	mvaddch (3, 7, ACS_PLUS);

	current_x = 1;
	current_y = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			move (current_y, current_x);
			mvprintw (current_y, current_x, "%c", board[i][j]);
			current_x += 4;
		}
		current_y += 2;
		current_x = 1;
	}
}

int getIndex (const char * prompt, const char * errorPrompt)
{
	int index;
	while (1) {
		mvprintw (10, 0, "%s", prompt);
		scanw ("%d", &index);
		if (index < 1 || index > 9) {
			mvprintw (12, 0, errorPrompt);
		} else {
			break;
		}
	}
}
