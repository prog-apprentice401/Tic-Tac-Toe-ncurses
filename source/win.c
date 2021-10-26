#include "misc.h"
#include "win.h"

int checkWin (char board[3][3], Player currentPlayer)
{
	char markToSearch = (currentPlayer == PLAYER_1) ? 'X' : 'O'; 

	if (checkRow (board, markToSearch)
		|| checkCol (board, markToSearch)
		|| checkDiag (board, markToSearch)) {
		return 1;
	} /*else if (checkTie (board, markToSearch)) {
		return 0;
	} */else {
		return -1;
	}
}

int checkRow (char board [3][3], char markToSearch)
{
	_Bool winState = 0;

	for (int i = 0; i < 3 && !winState; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != markToSearch) {
				winState = 0;
				break;
			}
			winState = 1;
		}
	}

	return winState;
}

int checkCol (char board[3][3], char markToSearch)
{
	_Bool winState = 0;

	for (int i = 0; i < 3 && !winState; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[j][i] != markToSearch) {
				winState = 0;
				break;
			}
			winState = 1;
		}
	}
	
	return winState;
}

int checkDiag (char board[3][3], char markToSearch)
{
	_Bool winState = 0;
	int i = 0;
	int j = 0;

	for (int diff = 1; diff >= -1 && !winState; diff -= 2) {
		for (; i < 3  &&  j < 3 && j >= 0; i++, j += diff) {
			if (board[i][j] != markToSearch) {
				winState = 0;
				break;
			}
			winState = 1;
		}
		i = 0;
	}
	return winState;
}
