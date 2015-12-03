#include "TTTBoard.h"

TTTBoard::TTTBoard(int boardWidth, int boardHeight, int padding)
{
	//TODO:Fix incorrect drawing positions in drawCell
	this->padding = padding;
	this->cellWidth = (boardWidth-padding*2) / 3.0;
	this->cellHeight = (boardHeight-padding*2) / 3.0;
		
	shape_X.setSize(sf::Vector2f(item_width, cellHeight - padding));
	shape_X.setOrigin(shape_X.getSize() / static_cast<float>(2));

	shape_X.setFillColor(X_COLOR);


	shape_O.setRadius(cellHeight/2 - padding);
	shape_O.setOrigin(sf::Vector2f(shape_O.getRadius() / 2.0 , 
								   shape_O.getRadius() / 2.0 ));
	shape_O.setOutlineThickness(item_width);
	shape_O.setPointCount(64);

	shape_O.setOutlineColor(O_COLOR);
	shape_O.setFillColor(sf::Color::Transparent);

	clearBoard();

	//For debugging
	this->setCell(0, 0, Cell::X);
	//this->setCell(2, 2, Cell::O);
}


TTTBoard::~TTTBoard()
{
}

void TTTBoard::drawCell(sf::RenderWindow* window, unsigned int index)
{
	if (this->getCell(index) == Cell::X)
	{
		shape_X.setPosition((index % 3) * (cellWidth + padding / 2) + cellWidth/2,
			(index / 3 ) * (cellHeight + padding / 2) + cellHeight/2);
		shape_X.move(sf::Vector2f(padding/3*2, padding/3*2));
		shape_X.setRotation(45);
		window->draw(shape_X);
		shape_X.setRotation(-45);
		window->draw(shape_X);
	}
	else if (this->getCell(index) == Cell::O)
	{
		shape_O.setPosition((index % 3) * cellWidth + cellWidth / 2 + padding/2,
			(index / 3) * cellHeight + cellHeight / 2 + padding/2);
		//shape_O.move(-padding / 2, -padding / 2);
		//shape_O.setRotation(index * 10);
		window->draw(shape_O);
	}
}


void TTTBoard::drawBoard(sf::RenderWindow* window)
{
	for (auto i = 0; i < 9; i++)
	{
		if (this->getCell(i) != Cell::Empty)
		{
			this->drawCell(window, i);
		}
	}
}

void TTTBoard::clearBoard()
{
	for (auto i = 0; i < 9; i++)
		cells[i % 3][i / 3] = { Cell::O };
}

