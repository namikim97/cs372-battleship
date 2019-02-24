// board.cpp
//
// 9 Feb 2019
// 22 Feb 2019
//
// Source for class Board.

#include "board.hpp"


// ********************************************************************
// CONSTRUCTORS AND DESTRUCTOR
// ********************************************************************

// Set default Board to 100 empty spaces
Board::Board(): _board(100, Board::STATE::EMPTY) { };

// Construct Board from a packet
// Assumes Board was added to an empty sf::Packet via operator<<
Board::Board(sf::Packet & packet): Board()
{
	for (auto j = 0; j < 10; ++j)
	{
		for (auto i = 0; i < 10; ++i)
		{
			pos_t position{i, j};
			sf::Uint8 value;
			packet >> value;
			set(position, (Board::STATE) value);
		}
	}
}


// ********************************************************************
// QUERY MEMBER FUNCTIONS
// ********************************************************************

Board::STATE Board::get(pos_t position) const
{
	return _board[position.x + position.y * 10];
}

bool Board::areAllShipsDead() const
{
	for (const auto & state : _board)
	{
		if (state == Board::STATE::SHIP)
			return false;
	}

	return true;
}


// ********************************************************************
// MODIFIER MEMBER FUNCTIONS
// ********************************************************************

bool Board::placeShip(pos_t position, int length, Board::DIR direction)
{
	if (!positionIsValid(position) || length < 1)
	{
		return false;
	}

	switch (direction)
	{
		default:
			return false;

		case Board::DIR::DOWN:
			if (position.y + length > 10)
			{
				return false;
			}
			else
			{
				for (auto i = position.y; i < position.y + length; ++i)
				{
					pos_t currentPosition{position.x, i};
					if (get(currentPosition) != Board::STATE::EMPTY)
					{
						return false;
					}
				}

				for (auto i = position.y; i < position.y + length; ++i)
				{
					pos_t currentPosition{position.x, i};
					set(currentPosition, Board::STATE::SHIP);
				}

				return true;
			}

		case Board::DIR::RIGHT:
			if (position.x + length > 10)
			{
				return false;
			}
			else
			{
				for (auto i = position.x; i < position.x + length; ++i)
				{
					pos_t currentPosition{i, position.y};
					if (get(currentPosition) != Board::STATE::EMPTY)
					{
						return false;
					}
				}

				for (auto i = position.x; i < position.x + length; ++i)
				{
					pos_t currentPosition{i, position.y};
					set(currentPosition, Board::STATE::SHIP);
				}

				return true;
			}
	}
}

bool Board::shoot(pos_t position)
{
	if (!positionIsValid(position))
	{
		return false;
	}

	switch (get(position))
	{
		case Board::STATE::SHIP:
			set(position, Board::STATE::HIT);
			return true;
		case Board::STATE::EMPTY:
			set(position, Board::STATE::MISS);
			return true;
		default:
			return false;

	}
}


// ********************************************************************
// PRIVATE HELPER FUNCTIONS
// ********************************************************************

// Assumes positionIsValid(position) is true.
void Board::set(pos_t position, Board::STATE state)
{
	_board[position.x + 10*position.y] = state;
}


// ********************************************************************
// PUBLIC HELPER FUNCTIONS
// ********************************************************************

bool positionIsValid(Board::pos_t position)
{
	return (0 <= position.x && position.x < 10)
			&& (0 <= position.y && position.y < 10);
}

// Used to transmit a packet containing board
// Assumes that if the packet has other content it is removed in-order
// and the receiver will construct a new Board via the
// sf::Packet-param constructor in the order of the original addition
sf::Packet & operator<<(sf::Packet & packet, const Board & board)
{
	for (auto j = 0; j < 10; ++j)
	{
		for (auto i = 0; i < 10; ++i)
		{
			sf::Uint8 value = (sf::Uint8) board.get({i, j});
			packet << value;
		}
	}
	return packet;
}


sf::Packet & operator<<(sf::Packet & packet, const Board::pos_t & position)
{
	sf::Uint8 x = (sf::Uint8) position.x;
	sf::Uint8 y = (sf::Uint8) position.y;

	packet << x;
	packet << y;

	return packet;
}


sf::Packet & operator>>(sf::Packet & packet, Board::pos_t & position)
{
	sf::Uint8 x, y;

	packet >> x;
	packet >> y;

	position.x = (int) x;
	position.y = (int) y;

	return packet;
}