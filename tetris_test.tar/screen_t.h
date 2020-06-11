/*****************************************************************
*								 *
*			skeleton code				 *
*			작성자: 송창헌 				 *
*								 *
******************************************************************/
#ifndef _SCREEN
#define _SCREEN

#include "tetromino_t.h"
#include <iostream>
#include <curses.h>


class Screen
{
private:
	WINDOW *wingame;
	WINDOW *winscore;
	WINDOW *winuser;

	int x,y;

	int board[18][10];
	int score;
	char* name;
	int randNum;
	int rotateNum;
	Block *block_array[1];
	
public:

	Screen();
	void printGameBoard();
	void printScoreBoard();
	void printResult();
	int moveBlock(int dir);
	void checkLine();
	bool isCollision(int a, int b);
	~Screen();
};

#endif
