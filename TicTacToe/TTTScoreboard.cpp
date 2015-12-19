#include "TTTScoreboard.h"
#include "Constants.h"

TTTScoreboard::TTTScoreboard(TTTBoard board)
{
	this->shapeX = board.getX();
	this->shapeO = board.getO();
}

void TTTScoreboard::drawScoreboard(sf::RenderWindow& window) const
{
	sf::RectangleShape seperator(sf::Vector2f(WIDTH - padding * 4, 2));

	seperator.setPosition(padding * 2, HEIGHT - 10);
	seperator.setFillColor(LINE_COLOR);
	window.draw(seperator);

	auto shapeXScore(shapeX);

	shapeXScore.setSize(sf::Vector2f(10, SCOREBOARD_HEIGHT));
	shapeXScore.setOrigin(shapeXScore.getSize() / static_cast<float>(2));
	shapeXScore.setPosition(padding * 4, HEIGHT + SCOREBOARD_HEIGHT - padding - 10);
	shapeXScore.setRotation(45);
	window.draw(shapeXScore);
	shapeXScore.setRotation(-45);
	window.draw(shapeXScore);

	auto shapeOScore(shapeO);

	shapeOScore.setRadius(SCOREBOARD_HEIGHT / 4);
	shapeOScore.setOutlineThickness(12);
	shapeOScore.setPointCount(32);
	shapeOScore.setOrigin(sf::Vector2f(shapeOScore.getRadius(), shapeOScore.getRadius()));

	shapeOScore.setPosition(padding * 2 + WIDTH / 2, HEIGHT + SCOREBOARD_HEIGHT - padding - 10);
	window.draw(shapeOScore);

	sf::CircleShape dot(6);

	dot.setPointCount(4);
	dot.setOrigin(sf::Vector2f(dot.getRadius(), dot.getRadius()));

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
}
