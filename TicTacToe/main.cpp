#include <SFML/Graphics.hpp>
#include "TTTBoard.h"

const auto WIDTH = 600;
const auto HEIGHT = 600;

// Color theme from here: https://color.adobe.com/Campfire-color-theme-2528696/
const auto BG_COLOR = sf::Color(140, 70, 70);
const auto LINE_COLOR = sf::Color(217, 100, 89);

//Board padding in pixels
const auto padding = 30;

static void drawLines(sf::RenderWindow*);

int WinMain()
{

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tic Tac Toe",
			 sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	TTTBoard board(WIDTH, HEIGHT, padding);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(BG_COLOR);

		drawLines(&window); // Draw lines comprising the board
		board.drawBoard(&window); // Draw X's and O's

		window.display();
	}

	return 0;
}

//Draw the lines comprising the Tic Tac Toe board
static void drawLines(sf::RenderWindow* window)
{
	auto lineWidth = 10;

	sf::RectangleShape line(sf::Vector2f(lineWidth, HEIGHT - padding * 2));
	line.setFillColor(LINE_COLOR);

	for (auto i = 1; i < 3; i++)
	{
		line.setPosition(WIDTH / 3 * i, padding);
		window->draw(line);
	}
	line.setSize(sf::Vector2f(WIDTH - padding *2 , lineWidth));
	for (auto i = 1; i < 3; i++)
	{
		line.setPosition( padding, HEIGHT / 3 * i);

		window->draw(line);
	}
}