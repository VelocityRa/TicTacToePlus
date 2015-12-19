#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "TTTScoreboard.h"

class TTTScoreboard;	//Forward declaration

// Store the cells and handles basic Tic Tac Toe logic
class TTTBoard
{
private:

	float cellWidth;
	float cellHeight;
	float windowWidth;
	float windowHeight;
	const float item_width = 15;

	//cells[3][3] and currentCell are defined at the end (we need the Cell enum)

	sf::RectangleShape shapeX;
	sf::CircleShape shapeO;
	
	TTTScoreboard* scoreboard;		// Pointer to the scoreboard associated with this board
	
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

	enum class Cell
	{
		Empty,
		X,
		O
	};

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
	
	void setScoreboard(TTTScoreboard* scoreboard_)
	{
		this->scoreboard = scoreboard_;
	}
	
	void setWinState(unsigned int i, unsigned int j)
	{
		const auto cell = getCell(i, j);
		gamestate = cell == Cell::X ? XWon : OWon;

		cell == Cell::X ? scoreboard->addPointX() : 
						  scoreboard->addPointO();
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

private:
	Cell cells[3][3];
	Cell currentCell; // Indicates current player

};
