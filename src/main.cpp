// main.cpp
//
// Created: 9 Feb 2019
// Updated: 23 Feb 2019
//
// Simple program to illustrate text-based game.
// Basic SFML app copied from the SFML tutorial (Drawing 2-D Stuff).

#include <SFML/Graphics.hpp>
#include "local_textGame.hpp"
#include "network_textGame.hpp"
#include "board.hpp"
#include "textUtils.hpp"

#include <iostream>

void printUsageMessage(char const *argv[])
{
	std::cout << "\n  Usage: \""<< argv[0]
		<< " (help | network-text | local-text | sfml)\"\n" << std::endl;
}

int main(int argc, char const *argv[])
{
	if (argc == 1)
	{
		printUsageMessage(argv);
		return 0;
	}

	std::string arg(argv[1]);
	str_tolower(arg);

	if ((argc == 1) || arg == "h" || arg == "-h" || arg == "help")
	{
		printUsageMessage(argv);
		return 0;
	}
	if (arg == "n" || arg == "net" || arg == "network" || arg == "network-text")
	{
		network_textGame();
		return 0;
	}
	else if (arg == "l" || arg == "local" || arg == "local-text")
	{
		local_textGame();
		return 0;
	}
	else if (arg == "s" || arg == "sfml")
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

	printUsageMessage(argv);
	return 0;
}