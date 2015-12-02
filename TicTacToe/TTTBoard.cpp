#include "TTTBoard.h"


TTTBoard::TTTBoard()
{
}


TTTBoard::~TTTBoard()
{
}



void TTTBoard::clearBoard()
{
	for (auto i = 0; i < 9; i++)
		cells[i % 3][i / 3] = { Empty };
}
