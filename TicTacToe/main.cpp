#include <SFML/Graphics.hpp>

int WinMain()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}