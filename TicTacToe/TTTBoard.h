#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

// Store the cells and handles basic Tic Tac Toe logic
class TTTBoard
{
private:

	enum class Cell
	{
		Empty,
			X,
			O
	};

	Cell cells[3][3];

public:
	TTTBoard();
	~TTTBoard();

	Cell getCell(unsigned int i)
	{
		return cells[i % 3][i / 3];
	}

	Cell getCell(unsigned int i, unsigned int j)
	{
		return cells[i][j];
	}

	void setCell(unsigned int i, unsigned int j, Cell cell)
	{
		cells[i][j] = cell;
	}

	void drawCells(sf::RenderWindow*);

	void clearBoard();
};
