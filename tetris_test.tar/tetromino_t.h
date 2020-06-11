/*****************************************************************
*								 *
*			skeleton code				 *
*			작성자: 송창헌 				 *
*								 *
******************************************************************/
#ifndef TETROMINO
#define TETROMINO

class Block
{
private:
	static const int width = 4;
	int board[width][width];
public:
	Block()
	{
		for(int i = 0 ; i < width;i++)
			for(int j = 0; j <width; j++)
				board[i][j] = 0;
	}
	void Block_init()
	{
		for(int i = 0 ; i < width;i++)
			for(int j = 0; j <width; j++)
				board[i][j] = 0;
	}
	void setBlock(int x,int y,int value)
	{
		if(x < 0 || y < 0 || x >= width || y>= width)	return;

		board[x][y] = value;
	}				
	int get_shape(const int x,const int y)
	{
		if(x < 0 || y < 0 || x >= width || y>= width);
		return board[x][y];	
	}
	virtual void rotate_block(int x, int y,int rotate_num)
	{
		if(x < 0 || y < 0 || x >= width || y>= width)	return;
	}
	~Block();
};

class O_block : public Block							
{
private:
	static const int width = 4;
	int board[width][width];
public:
	O_block();
	virtual void rotate_block(int x, int y,int rotate_num){};
	~O_block();
};

#endif
