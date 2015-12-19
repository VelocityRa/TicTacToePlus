#include "TTTBoard.h"
#include "Constants.h"

//Set up some basic variables and shapes used for drawing
TTTBoard::TTTBoard(int boardWidth, int boardHeight)
{
	currentCell = Cell::X;

	this->cellWidth = boardWidth / 3.0;
	this->cellHeight = boardHeight / 3.0;
	this->windowWidth = cellWidth * 3 + padding * 2;
	this->windowHeight = cellHeight * 3 + padding * 2;

		
	shapeX.setSize(sf::Vector2f(item_width, cellHeight - padding));
	shapeX.setOrigin(shapeX.getSize() / static_cast<float>(2));
	shapeX.setFillColor(X_COLOR);

	shapeO.setRadius(cellHeight/2.0 - padding - item_width);
	shapeO.setPointCount(64);
	shapeO.setOrigin(sf::Vector2f(shapeO.getRadius(), shapeO.getRadius()));
	shapeO.setOutlineThickness(item_width);
	shapeO.setOutlineColor(O_COLOR);
	shapeO.setFillColor(sf::Color::Transparent);

	clearBoard();
}

void TTTBoard::drawCell(sf::RenderWindow* window, unsigned int index)
{
	if (this->getCell(index) == Cell::X)
	{
		shapeX.setPosition(index % 3 * cellWidth + cellWidth / 2 + padding,
							index / 3 * cellHeight + cellHeight / 2 + padding);

		shapeX.setRotation(45);
		window->draw(shapeX);
		shapeX.setRotation(-45);
		window->draw(shapeX);
	}
	else if (this->getCell(index) == Cell::O)
	{
		shapeO.setPosition(index % 3 * cellWidth + cellWidth / 2 + padding,
							index / 3 * cellHeight + cellHeight / 2 + padding);

		window->draw(shapeO);
	}
}


void TTTBoard::drawScoreboard(sf::RenderWindow* window) const
{
	sf::RectangleShape seperator(sf::Vector2f(WIDTH-padding*4, 2));
	
	seperator.setPosition(padding*2, HEIGHT - 10);
	seperator.setFillColor(LINE_COLOR);
	window->draw(seperator);

	auto shapeXScore(shapeX);

	shapeXScore.setSize(sf::Vector2f(item_width/1.5, SCOREBOARD_HEIGHT));
	shapeXScore.setOrigin(shapeXScore.getSize() / static_cast<float>(2));
	shapeXScore.setPosition(padding * 4 , HEIGHT + SCOREBOARD_HEIGHT - padding - 10);
	shapeXScore.setRotation(45);
	window->draw(shapeXScore);
	shapeXScore.setRotation(-45);
	window->draw(shapeXScore);

	auto shapeOScore(shapeO);

	shapeOScore.setRadius(SCOREBOARD_HEIGHT/4);
	shapeOScore.setOutlineThickness(item_width/1.2);
	shapeOScore.setPointCount(32);
	shapeOScore.setOrigin(sf::Vector2f(shapeOScore.getRadius(), shapeOScore.getRadius()));

	shapeOScore.setPosition(padding * 2 + WIDTH/2, HEIGHT + SCOREBOARD_HEIGHT - padding - 10);
	window->draw(shapeOScore);

	sf::CircleShape dot(6);

	dot.setPointCount(4);
	dot.setOrigin(sf::Vector2f(dot.getRadius(), dot.getRadius()));

	dot.setPosition(shapeXScore.getPosition() + sf::Vector2f(40, -12));
	dot.setFillColor(X_COLOR);
	window->draw(dot);
	dot.setPosition(shapeXScore.getPosition() + sf::Vector2f(40, 12));
	window->draw(dot);

	dot.setPosition(shapeOScore.getPosition() + sf::Vector2f(40, -12));
	dot.setFillColor(O_COLOR);
	window->draw(dot);
	dot.setPosition(shapeOScore.getPosition() + sf::Vector2f(40, 12));
	window->draw(dot);
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

void TTTBoard::processMouseInput(sf::Event::MouseButtonEvent* mouseEvent)
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

	//TODO: Generalize for n-sized grid

	// Check horizontal
	for (auto row = 0; row < 3; row++)
	{
		if (isEmpty(row * 3)) { continue; }
		if (getCell(0, row) == getCell(1, row) &&
			getCell(1, row) == getCell(2, row))
		{
			setWinState(0, row);
		}
	}

	// Check vertical
	for (auto col = 0; col < 3; col++)
	{
		if (isEmpty(col)) { continue; }
		if (getCell(col, 0) == getCell(col, 1) &&
			getCell(col, 1) == getCell(col, 2))
		{
			setWinState(col, 0);
		}
	}

	// Check diagonals
	if (getCell(0, 0) == getCell(1, 1) &&
		getCell(1, 1) == getCell(2, 2) ||
		getCell(2, 0) == getCell(1, 1) &&
		getCell(1, 1) == getCell(0, 2))
	{
		if (!isEmpty(1, 1))
			setWinState(1, 1);
	}

	// Check draw
	if(isGamePlaying() && isBoardFull())
	{
		setDraw();
	}

	// TODO: Add score
}

void TTTBoard::resetGame()
{
	clearBoard();
	gamestate = TTTBoard::Playing;
}
