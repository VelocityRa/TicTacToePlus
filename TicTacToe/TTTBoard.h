#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>

// Store the cells and handles basic Tic Tac Toe logic
class TTTBoard
{
private:

	float cellWidth;
	float cellHeight;
	float windowWidth;
	float windowHeight;
	const float item_width = 15;

	enum class Cell
	{
		Empty,
			X,
			O
	};

	Cell cells[3][3];
	Cell currentCell; // Indicates current player
	sf::RectangleShape shapeX;
	sf::CircleShape shapeO;

public:
	TTTBoard(int boardWidth, int boardHeight);
	~TTTBoard() {}

	enum GameState
	{
		Playing,
		XWon,
		OWon,
		Draw
	} gamestate;

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

	GameState getGameState()
	{
		return gamestate;
	}

	sf::RectangleShape getX() const
	{
		return shapeX;
	}
	sf::CircleShape getO() const
	{
		return shapeO;
	}
	void drawCell(sf::RenderWindow& window, unsigned int index);
	void drawBoard(sf::RenderWindow& window);
	void clearBoard();
	bool isBoardFull();

	void processMouseInput(sf::Event::MouseButtonEvent& mouseEvent);

	void setWinState(unsigned int i, unsigned int j)
	{
		gamestate = getCell(i, j) == Cell::X ? XWon : OWon;
	}

	void setDraw()
	{
		gamestate = Draw;
	}

	bool isGamePlaying() const
	{
		return gamestate == Playing;
	}

	void nextMove();

	void resetGame();

};
