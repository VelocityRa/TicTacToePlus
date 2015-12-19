#include "TTTScoreboard.h"
#include "TTTBoard.h"
#include "Constants.h"

TTTScoreboard::TTTScoreboard(TTTBoard& board): XScore(0), OScore(0)
{
	this->shapeXScore = board.getX();
	this->shapeOScore = board.getO();

	sf::Vector2f XPosition, OPosition;
	XPosition = OPosition = sf::Vector2f(padding * 4,
		HEIGHT + padding);
	OPosition.x += WIDTH / 2;

	const auto shapeThickness = 12;
	shapeXScore.setSize(sf::Vector2f(shapeThickness, SCOREBOARD_HEIGHT - 4));
	shapeXScore.setOrigin(shapeXScore.getSize() / static_cast<float>(2));
	shapeXScore.setPosition(XPosition);

	shapeOScore.setRadius(SCOREBOARD_HEIGHT / 4);
	shapeOScore.setOrigin(sf::Vector2f(shapeOScore.getRadius(), shapeOScore.getRadius()));
	shapeOScore.setPosition(OPosition);
	shapeOScore.setOutlineThickness(shapeThickness);
	shapeOScore.setPointCount(32);

	dot.setRadius(6);
	dot.setPointCount(4);
	dot.setOrigin(sf::Vector2f(dot.getRadius(), dot.getRadius()));

	
	if (!font.loadFromFile("../TicTacToe/resources/fonts/ONRAMP.ttf"))
	{
		return;
	}

	this->XScoreText.setString("0");
	this->OScoreText.setString("0");
	this->XScoreText.setFont(font);
	this->OScoreText.setFont(font);
	this->XScoreText.setCharacterSize(128);
	this->OScoreText.setCharacterSize(128);
	this->XScoreText.setPosition(XPosition + sf::Vector2f(50, -100));
	this->OScoreText.setPosition(OPosition + sf::Vector2f(50, -100));
}

void TTTScoreboard::drawScoreboard(sf::RenderWindow& window)
{
	sf::RectangleShape seperator(sf::Vector2f(WIDTH - padding * 4, 2));

	seperator.setPosition(padding * 2, HEIGHT - 10);
	seperator.setFillColor(LINE_COLOR);
	window.draw(seperator);

	shapeXScore.setRotation(45);
	window.draw(shapeXScore);
	shapeXScore.setRotation(-45);
	window.draw(shapeXScore);

	window.draw(shapeOScore);

	dot.setPosition(shapeXScore.getPosition() + sf::Vector2f(40, -12));
	dot.setFillColor(X_COLOR);
	window.draw(dot);
	dot.setPosition(shapeXScore.getPosition() + sf::Vector2f(40, 12));
	window.draw(dot);

	dot.setPosition(shapeOScore.getPosition() + sf::Vector2f(40, -12));
	dot.setFillColor(O_COLOR);
	window.draw(dot);
	dot.setPosition(shapeOScore.getPosition() + sf::Vector2f(40, 12));
	window.draw(dot);

	window.draw(XScoreText);
	window.draw(OScoreText);
}

