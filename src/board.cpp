// board.cpp
//
// 9 Feb 2019
// 18 Feb 2019
//
// source for the board class

#include "board.hpp"

// *****************************************************
// *** HELPER FUNCTIONS ***
// *****************************************************
bool positionIsValid(int pos_x, int pos_y) {
	return (0 <= pos_x && pos_x < 10) && (0 <= pos_y && pos_y < 10);
}


// *****************************************************
// *** PRIVATE HELPER FUNCTIONS ***
// *****************************************************
void Board::setPosition(int pos_x, int pos_y, Board::STATE state) 
{
	_board[pos_x + 10 * pos_y] = state;
}

bool Board::checkWin() const
{
	for (const auto & v : _board) {
		if(v == Board::STATE::SHIP) {
			return false;
		}
	}

	return true; 
}


// *****************************************************
// *** PUBLIC CTOR ***
// *****************************************************

Board::Board():_board(100, Board::STATE::EMPTY) {};


// *****************************************************
// *** PUBLIC MEMBER FUNCTIONS ***
// *****************************************************

bool Board::placeShip(int pos_x, int pos_y, int length, Board::DIR direction)
{
	if (!positionIsValid(pos_x, pos_y) || length < 1)
	{
		return false;
	}

	if (direction == Board::DIR::DOWN)
	{
		if (pos_y + length > 10)
		{
			return false;
		} else {
			for (int i = pos_y; i < pos_y + length; ++i)
			{
				if (getStatus(pos_x, i) != Board::STATE::EMPTY)
				{
					return false;
				}
			}
			for (int i = pos_y; i < pos_y + length; ++i)
			{
				setPosition(pos_x, i, Board::STATE::SHIP);
			}

			return true;
		}
	}if (direction == Board::DIR::RIGHT)
	{
		if (pos_x + length > 10)
		{
			return false;
		} else {
			for (int i = pos_x; i < pos_x + length; ++i)
			{
				if (getStatus(i, pos_y) != Board::STATE::EMPTY)
				{
					return false;
				}
			}
			for (int i = pos_x; i < pos_x + length; ++i)
			{
				setPosition(i, pos_y, Board::STATE::SHIP);
			}

			return true;
		}
	}

	return false;
}

int Board::shootLocation(int pos_x, int pos_y) 
{
	if (!positionIsValid(pos_x, pos_y))
	{
		return false;
	}

	if (getStatus(pos_x, pos_y) == Board::STATE::SHIP)
	{
		setPosition(pos_x, pos_y, Board::STATE::HIT);
		return true;
	}

	if (getStatus(pos_x, pos_y) == Board::STATE::EMPTY)
	{
		setPosition(pos_x, pos_y, Board::STATE::MISS);
		return true;
	}

	return false;
}

Board::STATE Board::getStatus(int pos_x, int pos_y) const 
{
	if(positionIsValid(pos_x, pos_y))
	{
		return _board[pos_x + 10 * pos_y];
	} 
	else {
		throw "Invalid position given to getStatus().";
	}
}

















