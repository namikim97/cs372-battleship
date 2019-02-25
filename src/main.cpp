// main.cpp
//
// Created: 9 Feb 2019
// Updated: 24 Feb 2019
//
// Main program to choose between local text-based game, networked text-based game or SFML application.
// Basic SFML app copied from the SFML tutorial (Drawing 2-D Stuff).

#include <SFML/Graphics.hpp>
#include "local_textGame.hpp"
#include "network_textGame.hpp"
#include "board.hpp"
#include "textUtils.hpp"
#include "gfxBoard.hpp"

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
		const auto WIDTH = 1100/2, HEIGHT = 600/2; 
		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Battleship");
		sf::CircleShape circle(300.f, 1000);

		// Example Board
		Board board;
		board.placeShip({4, 4}, 2, Board::DIR::RIGHT);
		board.placeShip({9, 7}, 3, Board::DIR::DOWN);

		board.shoot({2,5});
		board.shoot({7,4});
		board.shoot({4,5});
		board.shoot({9,9});

		// Some constants to govern board positions
		const sf::Vector2f BOARDSIZE(400.f/2, 400.f/2);
		const sf::Vector2f LEFTPOSITION(100.f/2, 100.f/2);
		const sf::Vector2f RIGHTPOSITION(600.f/2, 100.f/2);

		// GfxBoard is NOT a Board but rather holds a const reference to a Board
		// (It looks at the Board to draw but cannot modify)
		GfxBoard left(board, LEFTPOSITION, BOARDSIZE);
		left.enableShowShips();

		GfxBoard right(board, RIGHTPOSITION, BOARDSIZE);
		right.disableShowShips();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					break;
				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					auto button = event.mouseButton.button;

					Board::pos_t pos;
					switch (button)
					{
						default:
							break;
						case sf::Mouse::Button::Left:
							pos = left.getPositionOnBoard({event.mouseButton.x, event.mouseButton.y});
							std::cout << "LEFT at (" << pos.x << ", " << pos.y << ")" << std::endl;
							break;
						case sf::Mouse::Button::Right:
							pos = right.getPositionOnBoard({event.mouseButton.x, event.mouseButton.y});
							std::cout << "RIGHT at (" << pos.x << ", " << pos.y << ")" << std::endl;
							break;
					}
					continue;
				}
			}

			// "Erases" the existing graphics displayed in the window with the color Black
			window.clear(sf::Color::Black);

			// Draw commands are to be done back to front
			window.draw(left);
			window.draw(right);

			// Update the window
			window.display();
		}
		return 0;
	}

	printUsageMessage(argv);
	return 0;
}