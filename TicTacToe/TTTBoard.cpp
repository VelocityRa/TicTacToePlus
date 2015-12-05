#include "TTTBoard.h"

//Set up some basic variables and shapes used for drawing
TTTBoard::TTTBoard(int boardWidth, int boardHeight, int padding)
{
	currentCell = Cell::X;

	this->padding = padding;
	this->cellWidth = boardWidth / 3.0;
	this->cellHeight = boardHeight / 3.0;
		
	shape_X.setSize(sf::Vector2f(item_width, cellHeight - padding));
	shape_X.setOrigin(shape_X.getSize() / static_cast<float>(2));
	shape_X.setFillColor(X_COLOR);

	shape_O.setRadius(cellHeight/2.0 - padding - item_width);
	shape_O.setPointCount(64);
	shape_O.setOrigin(sf::Vector2f(shape_O.getRadius(), shape_O.getRadius()));
	shape_O.setOutlineThickness(item_width);
	shape_O.setOutlineColor(O_COLOR);
	shape_O.setFillColor(sf::Color::Transparent);

	clearBoard();
}

void TTTBoard::drawCell(sf::RenderWindow* window, unsigned int index)
{
	if (this->getCell(index) == Cell::X)
	{
		shape_X.setPosition(index % 3  * cellWidth + cellWidth/2 + padding,
			index / 3 * cellHeight + cellHeight/2 + padding);

		shape_X.setRotation(45);
		window->draw(shape_X);
		shape_X.setRotation(-45);
		window->draw(shape_X);
	}
	else if (this->getCell(index) == Cell::O)
	{
		shape_O.setPosition(index % 3 * cellWidth + cellWidth / 2 + padding,
			index / 3 * cellHeight + cellHeight / 2 + padding);

		window->draw(shape_O);
	}
}

void TTTBoard::drawBoard(sf::RenderWindow* window)
{
	for (auto i = 0; i < 9; i++)
	{
		if (!this->isEmpty(i))
		{
			this->drawCell(window, i);
		}
	}
}

void TTTBoard::clearBoard()
{
	for (auto i = 0; i < 9; i++)
		cells[i % 3][i / 3] = { Cell::Empty };
}

bool TTTBoard::isBoardFull()
{
	auto isFull = true;
	for (auto i = 0; i < 9; i++)
	{
		if(isEmpty(i))
		{
			isFull = false;
			break;
		}
	}
	return isFull;
}

void TTTBoard::processMouseInput(sf::Event::MouseButtonEvent* mouseEvent,
		const int windowWidth, const int windowHeight)
{
	auto x = mouseEvent->x;
	auto y = mouseEvent->y;

	if (x < padding || x > windowWidth - padding
		|| y < padding || y > windowHeight - padding)
	{
		// Player clicked out of the board
		return;
	}

	//Input coords include padding so we should subtract it
	x, y -= padding;

	const unsigned int cellX = x / cellWidth;
	const unsigned int cellY = y / cellHeight;

	if (isEmpty(cellX, cellY))
	{
		this->setCell(cellX, cellY, currentCell);
		this->nextMove();
	}
}

void TTTBoard::nextMove()
{
	// Switch current player
	currentCell = currentCell == Cell::X ? Cell::O : Cell::X;

	// TODO: Add a win screen instead of instant board clear
	// TODO: Add score
	if (isBoardFull())
	{
		clearBoard();
	}
}
