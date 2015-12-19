#pragma once
#include <SFML/Graphics/Color.hpp>

//Window resolution
const auto WIDTH = 600;
const auto HEIGHT = 600;
const auto SCOREBOARD_HEIGHT = 70;

// Color theme from here: https://color.adobe.com/Campfire-color-theme-2528696/
const auto BG_COLOR = sf::Color(140, 70, 70);
const auto LINE_COLOR = sf::Color(217, 100, 89);

const sf::Color X_COLOR = sf::Color(242, 227, 148);
const sf::Color O_COLOR = sf::Color(242, 174, 114);

//Board padding in pixels
const auto padding = 30;

//Line width for the board lines
const auto lineWidth = WIDTH / 50;

//Board width
const auto bWIDTH = WIDTH - padding * 2;
const auto bHEIGHT = HEIGHT - padding * 2;