#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>

// Store the cells and handles basic Tic Tac Toe logic
class TTTBoard
{
private:

	const sf::Color X_COLOR = sf::Color(242, 227, 148);
	const sf::Color O_COLOR = sf::Color(242, 174, 114);

	const float item_width = 15;
	float cellWidth;
	float cellHeight;
	int padding;

	enum class Cell
	{
		Empty,
			X,
			O
	};

	Cell cells[3][3];
	Cell currentCell; // Indicates current player
	sf::RectangleShape shape_X;
	sf::CircleShape shape_O;

public:
	TTTBoard(int boardWidth, int boardHeight, int padding);
	~TTTBoard() {}

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

	bool isEmpty(unsigned int i)
	{
		return getCell(i) == Cell::Empty;
	}

	bool isEmpty(unsigned int i, unsigned int j)
	{
		return getCell(i, j) == Cell::Empty;
	}

	void drawCell(sf::RenderWindow* window, unsigned int index);
	void drawBoard(sf::RenderWindow* window);
	void clearBoard();

	void processMouseInput(sf::Event::MouseButtonEvent* mouseEvent,
		const int windowWidth, const int windowHeight);

	void nextMove();

};
