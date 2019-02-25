// local_gfxGame.cpp
//
// Created: 24 Feb 2019
// Updated: 24 Feb 2019
//
// Source for local PC graphics-based Battleship game.

#include "local_gfxGame.hpp"


// ********************************************************************
// PUBLIC FUNCTIONS
// ********************************************************************

void local_gfxGame()
{
	const int P1_SETUP = 0, P2_SETUP = 1, P1_TURN = 2, P2_TURN = 3;
	auto state = P1_SETUP;

	const std::vector<int> ship_lengths = {2, 3, 3, 4, 5};
	auto count = 0;

	const auto WIDTH = 1100/2, HEIGHT = 600/2;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Battleship");

	Board p1, p2;

	const sf::Vector2f BOARDSIZE(400.f/2, 400.f/2);
	const sf::Vector2f LEFTPOSITION(100.f/2, 100.f/2);
	const sf::Vector2f RIGHTPOSITION(600.f/2, 100.f/2);

	GfxBoard left(p1, LEFTPOSITION, BOARDSIZE);
	left.enableShowShips();

	GfxBoard right(p2, RIGHTPOSITION, BOARDSIZE);
	right.disableShowShips();

	auto dir = Board::DIR::DOWN;
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
				Board::pos_t pos{-1,-1};

				if (state == P1_SETUP)
				{
					switch (button)
					{
						default:
							break;
						case sf::Mouse::Button::Left:
							pos = left.getPositionOnBoard({event.mouseButton.x, event.mouseButton.y});
							break;
						case sf::Mouse::Button::Right:
							dir = (dir == Board::DIR::DOWN)? Board::DIR::RIGHT : Board::DIR::DOWN;
							break;
					}

					if (p1.placeShip(pos, ship_lengths[count], dir))
					{
						++count;
						if (count == 5)
						{
							count = 0;
							dir = Board::DIR::DOWN;
							state = P2_SETUP;

							right.enableShowShips();
							left.disableShowShips();
						}
					}
				}
				else if (state == P2_SETUP)
				{
					switch (button)
					{
						default:
							break;
						case sf::Mouse::Button::Left:
							pos = right.getPositionOnBoard({event.mouseButton.x, event.mouseButton.y});
							break;
						case sf::Mouse::Button::Right:
							dir = (dir == Board::DIR::DOWN)? Board::DIR::RIGHT : Board::DIR::DOWN;
							break;
					}

					if (p2.placeShip(pos, ship_lengths[count], dir))
					{
						++count;
						if (count == 5)
						{
							dir = Board::DIR::DOWN;
							state = P1_TURN;

							left.enableShowShips();
							right.disableShowShips();
						}
					}

				}
				else if (state == P1_TURN)
				{
					switch (button)
					{
						default:
							break;
						case sf::Mouse::Button::Left:
							pos = right.getPositionOnBoard({event.mouseButton.x, event.mouseButton.y});
							break;
					}

					if (p2.shoot(pos))
					{
						state = P2_TURN;

						right.enableShowShips();
						left.disableShowShips();

						if (p2.areAllShipsDead())
						{
							std::cout << "P1 Won!" << std::endl;
							return;
						}
					}
				}
				else if (state == P2_TURN)
				{
					switch (button)
					{
						default:
							break;
						case sf::Mouse::Button::Left:
							pos = left.getPositionOnBoard({event.mouseButton.x, event.mouseButton.y});
							break;
					}

					if (p1.shoot(pos))
					{
						state = P1_TURN;

						left.enableShowShips();
						right.disableShowShips();

						if (p1.areAllShipsDead())
						{
							std::cout << "P2 Won!" << std::endl;
							return;
						}
					}
				}
			}

		}

		// if (state == P1_SETUP || state == P1_TURN)
		// {
		// 	left.enableShowShips();
		// 	right.disableShowShips();
		// }
		// else // if (state == P2_SETUP || state == P2_TURN)
		// {
		// 	right.enableShowShips();
		// 	left.disableShowShips();
		// }

		window.clear(sf::Color::Black);

		window.draw(left);
		window.draw(right);

		window.display();
	}

}
