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

//Board width
const auto bWIDTH = WIDTH - padding * 2;
const auto bHEIGHT = HEIGHT - padding * 2;

//Line width for board lines
const auto lineWidth = 10;


static void drawLines(sf::RenderWindow*, sf::RectangleShape* line);

int WinMain()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tic Tac Toe",
			 sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

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
					board.processMouseInput(&event.mouseButton, WIDTH, HEIGHT);
				break;
			}
		}

		window.clear(BG_COLOR);

		drawLines(&window, &line); // Draw lines comprising the board
		board.drawBoard(&window); // Draw X's and O's

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
