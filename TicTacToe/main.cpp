#include "TTTBoard.h"
#include "TTTScoreboard.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

static void drawLines(sf::RenderWindow&, sf::RectangleShape& line);
static void setupWinText(sf::Text& text, sf::Text& shadow);
inline bool updateGOText(sf::Text& gameOverText, TTTBoard& board);

int WinMain()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT+SCOREBOARD_HEIGHT), "Tic Tac Toe",
			 sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(60);
	
	// Text stuff
	sf::Font font;
	if(!font.loadFromFile("../TicTacToe/resources/fonts/ONRAMP.ttf"))
	{
		return 1;
	}
	sf::Text gameOverText("", font, WIDTH/3);
	auto GOshadow(gameOverText);

	// Create the board
	TTTBoard board(bWIDTH, bHEIGHT);
	// Create the Scoreboard
	TTTScoreboard scoreboard(board);

	// Get pointer of this board's scoreboard so that
	// we can call it's methods/change it
	board.setScoreboard(&scoreboard);

	//Line(rectangle) shape used for drawing the board
	sf::RectangleShape line(sf::Vector2f(lineWidth, bHEIGHT));
	line.setFillColor(LINE_COLOR);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) 
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (board.isGamePlaying())
					{
						board.processMouseInput(event.mouseButton);
					}
					else // Clicked at win screen, so start a new game
					{
						gameOverText.setString("");
						GOshadow.setString("");
						board.resetGame();
						break;
					}
					if (updateGOText(gameOverText, board)) break;
					setupWinText(gameOverText, GOshadow);
				}
				break;
			}
		}

		window.clear(BG_COLOR);

		drawLines(window, line); // Draw lines comprising the board
		board.drawBoard(window); // Draw X's and O's
		scoreboard.drawScoreboard(window); //Draw scoreboard (seperator, 

		window.draw(GOshadow);  // Draw game over text's shadow
		window.draw(gameOverText); // Draw winning text (empty if game is in progress)

		window.display();
	}

	return 0;
}

//Draw the lines comprising the Tic Tac Toe board
static void drawLines(sf::RenderWindow& window, sf::RectangleShape& line)
{
	line.setSize(sf::Vector2f(lineWidth, bHEIGHT));
	for (auto i = 1; i < 3; i++) //Horizontal lines
	{
		line.setPosition(bWIDTH / 3 * i, 0);
		line.move(padding - lineWidth/2, padding);
		window.draw(line);
	}
	line.setSize(sf::Vector2f(bWIDTH, lineWidth));
	for (auto i = 1; i < 3; i++) //Vertical lines
	{
		line.setPosition(0, bHEIGHT / 3 * i);
		line.move(padding, padding - lineWidth/2);
		window.draw(line);
	}
}

static void setupWinText(sf::Text& text, sf::Text& shadow)
{
	// Position winning text to center and center align it
	text.setPosition(0, 0);
	text.setOrigin(0, 0);

	auto textRect = text.getGlobalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(WIDTH / 2, HEIGHT / 2);

	//Create its shadow and offset it
	shadow = text;
	shadow.move(10, -10);
	shadow.setColor(sf::Color::Black);
}

inline static bool updateGOText(sf::Text& gameOverText, TTTBoard& board)
{
	auto gamestate = board.getGameState();
	if (gamestate == TTTBoard::XWon) {
		gameOverText.setString("X WON");
	}
	else if (gamestate == TTTBoard::OWon) {
		gameOverText.setString("O WON");
	}
	else if (gamestate == TTTBoard::Draw) {
		gameOverText.setString("DRAW");
	}
	else
		return true;
	return false;
}
