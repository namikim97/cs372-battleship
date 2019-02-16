// main.cpp
//
// Created: 2 Feb 2019
// Updated: 2 Feb 2019
//
// Simple program to illustrate SFML integration.
// Copied from the SFML tutorial for Drawing 2-D Stuff.

#include <SFML/Graphics.hpp>
#include "board.hpp"


int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "Battleship");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		window.display();
	}

	return 0;
}