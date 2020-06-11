/*****************************************************************
*								 *
*			skeleton code				 *
*			작성자: 송창헌 				 *
*								 *
******************************************************************/
#include <iostream>
#include <curses.h>
#include "tetromino_t.h"


O_block::O_block() : Block()
{
	Block_init();
	setBlock(0,0,1);
	setBlock(0,1,1);
	setBlock(1,0,1);
	setBlock(1,1,1);
}
