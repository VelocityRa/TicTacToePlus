#include "TTTBoard.h"


TTTBoard::TTTBoard()
{
	clearBoard();

}


TTTBoard::~TTTBoard()
{
}


void TTTBoard::drawCells(sf::RenderWindow* window)
{
	for (auto i = 0; i < 9; i++)
	{
		if (this->getCell(i) != Cell::Empty)
		{
			//TODO: Draw cell
			//window.draw();
		}
	}
}

void TTTBoard::clearBoard()
{
	for (auto i = 0; i < 9; i++)
		cells[i % 3][i / 3] = { Cell::Empty };
}
