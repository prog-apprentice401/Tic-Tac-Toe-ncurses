#ifndef __WIN_H__
	#define __WIN_H__
	
	#include "misc.h"

	int checkWin (char[3][3], Player);
	static int checkDiag (char[3][3], char);
	static int checkCol (char[3][3], char);
	static int checkRow (char[3][3], char);
	static int checkTie (char[3][3], char);
#endif
