// board.hpp
//
// Created: 9 Feb 2019
// Updated: 9 Feb 2019
//
// a board class 

#ifndef FILE_BOARD_HPP_INCLUDED
#define FILE_BOARD_HPP_INCLUDED

#include <vector>

class Board {
public:
	enum DIR{
		DOWN = 0,
		RIGHT = 1
	};

	enum STATE {
		EMPTY = 0,
		SHIP = 1,
		MISS = 2,
		HIT = 3
	};

	// default ctor and dtor
	Board(); 
	~Board() = default;

	// delete the rest of the big5
	Board(const Board & board) = delete; //copy ctor
	Board(Board && board) = delete; //mov dtor
	Board & operator=(const Board & board) = delete; //copy ass
	Board & operator=(Board && board) = delete; //mov ass

	// public member function
	bool placeShip(int pos_x, int pos_y, int length, Board::DIR direction);
	int shootLocation(int pos_x, int pos_y);
	Board::STATE getStatus(int pos_x, int pos_y) const; //get state of the location 
	bool checkWin() const;

private:
	std::vector<Board::STATE> _board;

	void setPosition(int pos_x, int pos_y, Board::STATE state);
};


#endif // #ifndef FILE_BOARD_HPP_INCLUDED