/*****************************************************************
*								 *
*			skeleton code				 *
*			작성자: 송창헌 				 *
*								 *
******************************************************************/

#include "screen_t.h"
#include "tetromino_t.h"

Screen::Screen()
{
	char *name = new char[20];

	std::cout << "--테트리스 게임--" << std::endl << "게임을 시작합니다." << std::endl;
	std::cout << " 사용자의 이름을 입력해주세요! " << std::endl;
	std::cout << " 이름(5자 이내) : ";
	std::cin >> name;

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);

	resize_term(25,50);			// sizing terminal size
	
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_BLACK);							
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_YELLOW,COLOR_YELLOW);
	
	block_array[0] = new O_block();
	
	border('|','|','-','-','+','+','+','+');
	refresh();

	wingame = newwin(20, 22, 2 ,2);
	wborder(wingame,'|','|','-','-','+','+','+','+');

	for(int row=0; row < 18 ; row++)
		for(int col=0; col < 10 ; col++)
			board[row][col] = 0;

	x = 0, y =4;
	rotateNum = 0;
	randNum = 0;

	printGameBoard();

	winscore =newwin(4,10,4,30);
	wborder(winscore,'|','|','-','-','+','+','+','+');
	wattron(winscore, COLOR_PAIR(2));
	mvwprintw(winscore, 1, 1, "score: ");
	wattroff(winscore,COLOR_PAIR(2));

	wrefresh(winscore);

	score = 0;
	printScoreBoard();

	winuser = newwin(4, 10, 10, 30);
	wborder(winuser, '|', '|', '-', '-', '+', '+', '+', '+');
	wattron(winuser, COLOR_PAIR(1));
	mvwprintw(winuser, 1, 1, "name: ");
	mvwprintw(winuser, 2, 1, name);
	wattroff(winuser,COLOR_PAIR(1));

	wrefresh(winuser);
}


void Screen::printGameBoard()
{
	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 10; j ++)
		{
			if(board[i][j] != 0)
			{
				wattron(wingame, COLOR_PAIR(board[i][j]+2));
				mvwprintw(wingame, i+1, j*2+1, "  ");
				wattroff(wingame, COLOR_PAIR(board[i][j]+2));
			}
			else
			{
				wattron(wingame, COLOR_PAIR(1));
				mvwprintw(wingame, i+1, j*2+1, "  ");
				wattroff(wingame, COLOR_PAIR(1));
			}
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j <4; j++)
		{
			if(block_array[randNum] -> get_shape(i,j) != 0){
				wattron(wingame,COLOR_PAIR(block_array[randNum] -> get_shape(i,j) + 2));
				mvwprintw(wingame, x+i+1,(y+j)*2 +1,"  ");
				wattroff(wingame,COLOR_PAIR(block_array[randNum] -> get_shape(i,j) + 2));
			}
		}
	}
	wrefresh(wingame);
}

void Screen::printScoreBoard()
{
	wattron(winscore, COLOR_PAIR(2));

	mvwprintw(winscore,2,1,"%d ", score);
	wattroff(winscore, COLOR_PAIR(2));

	wrefresh(winscore);
}

void Screen::printResult()
{
	mvprintw(22, 10, "score is %d", score);
	mvprintw(23, 10, "Press any key to exit tetris");
}

int Screen::moveBlock(int dir)
{
	switch(dir)
	{
	case KEY_DOWN:
		if (!isCollision(1,0))
			x++;
		break;
	case KEY_LEFT:
		if (!isCollision(0,-1))
			y--;
		break;
	case KEY_RIGHT:
		if (!isCollision(0,1))
			y++;
		break;
	
	case 32:
		while (!isCollision(1,0))
			x++;
		break;
	}

	if (isCollision(1,0))  
	{
		for (int i = 0; i <  4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if(block_array[randNum] -> get_shape(i,j) != 0){
					board[x+i][y+j] = block_array[randNum] -> get_shape(i,j);
				}
			}
		}

		for (int j = 0; j < 10; j++)
		{
			if (board[0][j] != 0)
			{
				printGameBoard();
				return 1;
			}
		}

		x = 0, y = 4;
		rotateNum = 0;
		if (isCollision(1,0))
		{
			printGameBoard();
			return 1;
		}

	}
	checkLine();
	printScoreBoard();
	printGameBoard();
	
	

	return 0;
}


void Screen::checkLine()
{
	int i, j, k;
	int check;

	i = 17;

	while (i >= 0)
	{
		check = 1;

		for (j = 0; j<10; j++)
		{
			if (board[i][j] == 0)
			{
				check = 0;
				break;
			}
		}

		if (check == 1)
		{
			score += 1;
			for (k = i - 1; k >= 0; k--)
			{
				for (j = 0; j<10; j++)
				{
					board[k + 1][j] = board[k][j];
				}
			}
			for (j = 0; j<10; j++)
			{
				board[0][j] = 0;
			}

			continue;
		}

		i--;
	}

}

bool Screen::isCollision(int a,int b)
{
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(block_array[randNum] -> get_shape(i, j) != 0 && ((x + a + i) < 0 || (x + a + i) > 17 || (y + b + j) < 0 || (y + b + j) > 9 || board[x + a + i][y + b + j] != 0))
			{
				return true;
			}
		}
	}

	return false;
}


Screen::~Screen()
{
	delwin(wingame);
	delwin(winuser);
	delwin(winscore);
	endwin();
}
