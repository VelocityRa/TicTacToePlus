#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class TTTBoard;		//Forward declaration

class TTTScoreboard
{
private:
	sf::Font font;
	sf::RectangleShape shapeXScore;
	sf::CircleShape shapeOScore, dot;

	sf::Text XScoreText, OScoreText;
	unsigned int XScore, OScore;

public:
	explicit TTTScoreboard(TTTBoard& board);

	void drawScoreboard(sf::RenderWindow & window);

	void addPointX()
	{
		XScoreText.setString(std::to_string(++XScore));
	}

	void addPointO()
	{
		OScoreText.setString(std::to_string(++OScore));
	}

};
