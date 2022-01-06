#include <ctype.h>
#include "misc.h"
#include "win.h"

int checkWin (char * board, int sideLength, Player currentPlayer)
{
	char markToSearch = (currentPlayer == PLAYER_1) ? 'X' : 'O'; 

	if (checkRow (board, sideLength, markToSearch)
		|| checkCol (board, sideLength, markToSearch)
		|| checkDiag (board, sideLength, markToSearch)) {
		return 1;
	} else if (checkTie (board, sideLength)) {
		return 0;
	}
	return -1;
}

int checkRow (char * board, int sideLength, char markToSearch)
{
	_Bool winState = 0;

	for (int i = 0; i < sideLength && !winState; i++) {
		for (int j = 0; j < sideLength; j++) {
			if (board[i * sideLength + j] != markToSearch) {
				winState = 0;
				break;
			}
			winState = 1;
		}
	}

	return winState;
}

int checkCol (char * board, int sideLength, char markToSearch)
{
	_Bool winState = 0;

	for (int i = 0; i < sideLength && !winState; i++) {
		for (int j = 0; j < sideLength; j++) {
			if (board[j * sideLength + i] != markToSearch) {
				winState = 0;
				break;
			}
			winState = 1;
		}
	}
	
	return winState;
}

int checkDiag (char * board, int sideLength, char markToSearch)
{
	_Bool winState = 0;
	int i = 0;
	int j = 0;

	for (int diff = 1; diff >= -1 && !winState; diff -= 2) {
		for (; i < sideLength  &&  j < sideLength && j >= 0; i++, j += diff) {
			if (board[i * sideLength + j] != markToSearch) {
				winState = 0;
				break;
			}
			winState = 1;
		}
		i = 0;
	}
	return winState;
}

int checkTie (char * board, int sideLength)
{
	for (int i = 0; i < sideLength; i++) {
		for (int j = 0; j < sideLength; j++) {
			if (!isalpha (board[i * sideLength + j])) {
				return 0;	//there is an empty cell
			}
		}
	}
	return 1;	//all cells used
}
