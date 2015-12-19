#pragma once
#include "TTTBoard.h"

class TTTScoreboard
{
private:
	sf::RectangleShape shapeX;
	sf::CircleShape shapeO;

public:
	explicit TTTScoreboard(TTTBoard board);

	void drawScoreboard(sf::RenderWindow & window) const;

};
