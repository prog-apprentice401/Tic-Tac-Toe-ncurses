#ifndef __WIN_H__
	#define __WIN_H__
	
	#include "misc.h"

	int checkWin (char[3][3], Player);
	int checkDiag (char[3][3], char);
	int checkCol (char[3][3], char);
	int checkRow (char[3][3], char);
	int checkTie (char[3][3]);
#endif
