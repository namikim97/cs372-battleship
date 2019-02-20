// main.cpp
//
// Created: 9 Feb 2019
// Updated: 19 Feb 2019
//
// Simple program to illustrate text-based game.
// Basic SFML app copied from the SFML tutorial (Drawing 2-D Stuff).

#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "textBasedGame.hpp"

int main()
{
	// "ACTIVE" Illustrate basic text-based game
	textBasedGame();

	if (0) // "INACTIVE" A basic SFML app.
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
	}

	return 0;
}