#include <SFML/Graphics.hpp>
#include "TTTBoard.h"

//Window resolution
const auto WIDTH = 600;
const auto HEIGHT = 600;

// Color theme from here: https://color.adobe.com/Campfire-color-theme-2528696/
const auto BG_COLOR = sf::Color(140, 70, 70);
const auto LINE_COLOR = sf::Color(217, 100, 89);

//Board padding in pixels
const auto padding = 30;

//Line width for the board lines
const auto lineWidth = WIDTH / 50;

//Board width
const auto bWIDTH = WIDTH - padding * 2;
const auto bHEIGHT = HEIGHT - padding * 2;

static void drawLines(sf::RenderWindow*, sf::RectangleShape* line);
static void setupWinText(sf::Text* text, sf::Text* shadow);

int WinMain()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tic Tac Toe",
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
	TTTBoard board(bWIDTH, bHEIGHT, padding);

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
						board.processMouseInput(&event.mouseButton);
					}
					else
					{
						gameOverText.setString("");
						GOshadow.setString("");
						board.resetGame();
					}
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
					setupWinText(&gameOverText, &GOshadow);
				}
				break;
			}
		}

		window.clear(BG_COLOR);

		drawLines(&window, &line); // Draw lines comprising the board
		board.drawBoard(&window); // Draw X's and O's

		window.draw(GOshadow);  // Draw game over text's shadow
		window.draw(gameOverText); // Draw winning text (empty if game is in progress)

		window.display();
	}

	return 0;
}

//Draw the lines comprising the Tic Tac Toe board
static void drawLines(sf::RenderWindow* window, sf::RectangleShape* line)
{
	line->setSize(sf::Vector2f(lineWidth, bHEIGHT));
	for (auto i = 1; i < 3; i++) //Horizontal lines
	{
		line->setPosition(bWIDTH / 3 * i, 0);
		line->move(padding - lineWidth/2, padding);
		window->draw(*line);
	}
	line->setSize(sf::Vector2f(bWIDTH, lineWidth));
	for (auto i = 1; i < 3; i++) //Vertical lines
	{
		line->setPosition(0, bHEIGHT / 3 * i);
		line->move(padding, padding - lineWidth/2);
		window->draw(*line);
	}
}

static void setupWinText(sf::Text* text, sf::Text* shadow)
{
	// Position winning text to center and center align it
	text->setPosition(0, 0);
	text->setOrigin(0, 0);

	auto textRect = text->getGlobalBounds();
	text->setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text->setPosition(WIDTH / 2, HEIGHT / 2);

	//Create its shadow and offset it
	*shadow = *text;
	shadow->move(10, -10);
	shadow->setColor(sf::Color::Black);
}
