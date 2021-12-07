#ifndef __MISC_H__
	#define __MISC_H__

	typedef enum {
		PLAYER_1 = 1,
		PLAYER_2 = 2
	} Player;

	typedef enum {
		INVALID_INDEX,
		USED_CELL
	} Error;
	
	void handleError (Error);
#endif
