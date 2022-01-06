#ifndef __WIN_H__
	#define __WIN_H__
	
	#include "misc.h"

	int checkWin (char *, int, Player);
	int checkDiag (char *, int, char);
	int checkCol (char *, int, char);
	int checkRow (char *, int, char);
	int checkTie (char *, int);
#endif
