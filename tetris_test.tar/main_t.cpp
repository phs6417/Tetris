/*****************************************************************
*								 *
*			skeleton code				 *
*			작성자: 송창헌 				 *
*								 *
******************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include "tetromino_t.h"
#include "screen_t.h"

int main(int argc, char* argv[])
{
	std::ifstream inStream;

	Screen game;
	int key, state = 0;
	int seed;

	if (argc < 2)
	{
		while (state == 0)
		{
			key = getch();

			if (key == 'q') break;
			state = game.moveBlock(key);
		}

	}
	else
	{
		inStream.open(argv[1]);
		if (!inStream.fail())
		{
			while (1)
			{
				
				char ch;

				inStream >> ch;
				if (inStream.eof()) break;
				if (ch == 'q') break;

				switch (ch)
				{
				case 'l':
					game.moveBlock(KEY_LEFT);
					break;
				case 'r':
					game.moveBlock(KEY_RIGHT);
					break;
				case 'g':
					game.moveBlock(KEY_DOWN);
					break;
				case 'd':
					game.moveBlock(32);
					break;
				}

			}

		}
	}
	game.printResult();

	getch();
	return 0;
}
