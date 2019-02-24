// local_textGame.cpp
//
// Created: 18 Feb 2019
// Updated: 23 Feb 2019
//
// Source for local PC text-based Battleship game.

#include "local_textGame.hpp"


// ********************************************************************
// PUBLIC FUNCTIONS
// ********************************************************************

void promptForShipDirectionAndPosition(int length)
{
	std::cout << "Place a length " << length << " ship down or right starting at (x, y), input: 'D/r x y' ";
}

void promptToShootPosition()
{
	std::cout << "Shoot a location at (x, y), input: 'x y' ";
}

void placeShips(Board & board)
{
	const auto ship_lengths = { 2, 3, 3, 4, 5 };

	for (auto ship_length : ship_lengths)
	{
		print(board, true);

		while (true)
		{
			promptForShipDirectionAndPosition(ship_length);
			auto strDir = readToken();

			if (!isParseableShipDirection(strDir))
			{
				flush_cin();
				std::cout << "Invalid Direction..." << std::endl;
				continue;
			}

			auto dir = parseShipDirection(strDir);
			auto position = getPositionFromUser();

			if (!positionIsValid(position))
			{
				std::cout << "Invalid Position..." << std::endl;
				continue;
			}

			if (!board.placeShip(position, ship_length, dir))
			{
				std::cout << "Invalid Ship Placement..." << std::endl;
				continue;
			}

			break;
		}
	}
}

void printPlayerAndEnemy(const Board & player, const Board & enemy)
{
	std::cout << "Your Board: " << std::endl;
	print(player, true);
	std::cout << "\nYour Enemy's Board: " << std::endl;
	print(enemy, false);
}

Board::pos_t playerTurn(const Board & player, Board & enemy)
{
	printPlayerAndEnemy(player, enemy);

	Board::pos_t position;
	while (true)
	{
		promptToShootPosition();
		position = getPositionFromUser();

		if (enemy.shoot(position))
			break;
	}

	return position;

}

void local_textGame()
{
	Board p1, p2;
	std::cout << "Player 1 place your ships!" << std::endl;
	placeShips(p1);

	std::cout << std::endl << std::endl << std::endl << std::endl;

	std::cout << "Player 2 place your ships!" << std::endl;
	placeShips(p2);

	while (true)
	{
		std::cout << std::endl << "\n\nPlayer 1's turn to shoot!" << std::endl;

		playerTurn(p1, p2);
		if (p2.areAllShipsDead())
		{
			std::cout << "Player 1 Wins!" << std::endl;
			return;
		}

		std::cout << std::endl << "\n\nPlayer 2's turn to shoot!" << std::endl;
		playerTurn(p2, p1);
		if (p1.areAllShipsDead())
		{
			std::cout << "Player 2 Wins!" << std::endl;
			return;
		}
	}

}
