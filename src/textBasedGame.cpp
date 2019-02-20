// textBasedGame.cpp
//
// Created: 18 Feb 2019
// Updated: 19 Feb 2019
//
// Source for simple text-based Battleship

#include "textBasedGame.hpp"

// *****************************************************
// HELPER TYPES
// *****************************************************
struct pos_t {
	int x;
	int y;
};

// *****************************************************
// HELPER FUNCTIONS
// *****************************************************

// Alias to std:cin.ignore(<max stream limit>)
void ignoreRemainingInput()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool posIsValid(int x, int y)
{
	return (0 <= x && x < 10) && (0 <= y && y < 10);
}

pos_t promptForShipPos(int length)
{
	pos_t pos;
	do
	{
		if (!std::cin)
		{
			std::cin.clear();
			ignoreRemainingInput();
			std::cout << "Failed Input at - ShipPos\n" << std::endl;
		}
		std::cout << "Place a length " << length << " ship at 'x y': ";
		std::cin >> pos.x >> pos.y;
	} while (!std::cin || !posIsValid(pos.x, pos.y));

	std::cout << std::endl;

	return {pos.x, pos.y};
}

Board::DIR promptForDir()
{
	Board::DIR dir;
	std::string dir_str;

	auto notSuccessful = true;
	while (notSuccessful)
	{
		std::cout << "Down or right (D/r): ";
		std::cin >> dir_str;

		if (dir_str[0] == 'D' || dir_str[0] == 'd')
		{
			dir = Board::DIR::DOWN;
			notSuccessful = false;
		}
		else if (dir_str[0] == 'R' || dir_str[0] == 'r')
		{
			dir = Board::DIR::RIGHT;
			notSuccessful = false;
		}
		else {
			notSuccessful = true;
			ignoreRemainingInput();
			std::cout << "Failed Input at - Dir\n" << std::endl;
		}
	}

	std::cout << std::endl;

	return dir;
}

pos_t promptForShootPos()
{
	pos_t pos;
	do
	{
		if (!std::cin)
		{
			std::cin.clear();
			ignoreRemainingInput();
			std::cout << "Failed Input at - ShootPos\n" << std::endl;
		}
		std::cout << "Shoot your friend at 'x y': ";
		std::cin >> pos.x >> pos.y;
	} while (!std::cin && !posIsValid(pos.x, pos.y));

	return {pos.x, pos.y};
}


void print(const Board & board, bool showAll = false)
{
	for (auto j = 0; j < 10; ++j)
	{
		for (auto i = 0; i < 10; ++i)
		{
			switch (board.getStatus(i, j))
			{
				case Board::STATE::SHIP:
					if (showAll)
						std::cout << "S" << " ";
					else
					{
						case Board::STATE::EMPTY:
							std::cout << "O" << " ";
					}
					break;
				case Board::STATE::MISS:
					std::cout << "M" << " ";
					break;
				case Board::STATE::HIT:
					std::cout << "X" << " ";
					break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void placeShips(Board & board, const std::string & playerStr)
{
	auto ship_lengths = {2};

	std::cout << "Place your ships " << playerStr << ":" << std::endl;
	print(board, true);
	for (auto ship_length : ship_lengths)
	{
		std::string direction;

		while (true)
		{
			auto pos = promptForShipPos(ship_length);
			auto dir = promptForDir();

			if (board.placeShip(pos.x, pos.y, ship_length, dir))
			{
				print(board, true);
				break;
			}
			std::cout << "Failed Input at - placeShip\n" << std::endl;
		}
	}
}

bool playerTurn(const Board & player, Board & enemy, const std::string & playerStr)
{
	std::cout << "\n" << playerStr << " TURN!" << std::endl;

	std::cout << "YOUR BOARD: " << std::endl;
	print(player, true);
	std::cout << "\nENEMY BOARD: " << std::endl;
	print(enemy, false);

	pos_t pos;
	do {
		pos = promptForShootPos();
	} while (!enemy.shootLocation(pos.x, pos.y));

	std::cout << std::endl;
	ignoreRemainingInput();
	

	if (enemy.checkWin())
	{
		std::cout << "\n" << playerStr << " WON!" << std::endl;
		return true;
	}

	return false;
}

void textBasedGame()
{
	Board p1, p2;

	std::cout << std::endl;

	placeShips(p1, "P1");
	placeShips(p2, "P2");

	while (true) // Loop until a player wins...
	{
		if (playerTurn(p1, p2, "P1")) return;
		if (playerTurn(p2, p1, "P2")) return;
	}
}