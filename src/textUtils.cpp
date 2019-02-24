// textUtils.cpp
//
// Created: 22 Feb 2019
// Updated: 23 Feb 2019
//
// Header for some text-based utilities.

#include "textUtils.hpp"


// ********************************************************************
// PUBLIC FUNCTIONS
// ********************************************************************

// Alias to std:cin.ignore(<max stream limit>)
void flush_cin()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Prints a text-based version of the board
// By default, showAll ships is false
void print(const Board & board, bool showAll)
{
	std::cout << "     x - - - - - - - - >" << std::endl;
	std::cout << "     0 1 2 3 4 5 6 7 8 9" << std::endl;
	for (auto j = 0; j < 10; ++j)
	{
		if (j == 0)
		{
			std::cout << " y ";
		}
		else if (j == 9)
		{
			std::cout << " v ";
		}
		else
		{
			std::cout << " | ";
		}

		std::cout << j << "";
		for (auto i = 0; i < 10; ++i)
		{
			switch (board.get({i, j}))
			{
				case Board::STATE::SHIP:
					if (showAll)
					{
						std::cout << " S";
					}
					else
					{
						std::cout << " \u00B7";
					}
					break;
				case Board::STATE::EMPTY:
					std::cout << " \u00B7";
					break;
				case Board::STATE::MISS:
					std::cout << " M";
					break;
				case Board::STATE::HIT:
					std::cout << " X";
					break;
				default:
					std::cout << " @";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// Wrapper for std::cin to read a string input.
// Returns an empty string on a failed parse.
std::string readToken()
{
	std::string str;
	std::cin >> str;

	if (!std::cin || std::cin.eof())
	{
		flush_cin();
		std::cin.clear();
		str = "";
	}

	return str;
}


// Returns whether the string starts with a D/d or R/r.
// Used to verify a string is parseable as a Board::DIR.
bool isParseableShipDirection(const std::string & strDirection)
{
	return !strDirection.empty() && (strDirection[0] == 'D'
		|| strDirection[0] == 'd' || strDirection[0] == 'R'
		|| strDirection[0] == 'r');
}

// Call isParseableShipDirection() first to verify strDirection is
// parseable to either Board::DIR::DOWN or Board::DIR::RIGHT.
Board::DIR parseShipDirection(const std::string & strDirection)
{
	switch (strDirection[0])
	{
		default:
		case 'D':
		case 'd':
			return Board::DIR::DOWN;
		case 'R':
		case 'r':
			return Board::DIR::RIGHT;
	}
}

// Using std::cin, get a Board::pos_t. Ignores any remaining input
// for std::cin. Returns (-1, -1) on a failed parse.
Board::pos_t getPositionFromUser()
{
	Board::pos_t position;
	std::cin >> position.x >> position.y;

	if (!std::cin)
	{
		std::cin.clear();
		position = {-1, -1};
	}

	flush_cin();

	return position;
}

std::string & str_tolower (std::string & s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
};

std::string & str_toupper(std::string & s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return toupper(c); });
    return s;
}