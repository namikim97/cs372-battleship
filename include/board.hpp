// board.hpp
//
// Created: 9 Feb 2019
// Updated: 22 Feb 2019
//
// Source for class Board.

#ifndef FILE_BOARD_HPP_INCLUDED
#define FILE_BOARD_HPP_INCLUDED

#include <SFML/Network.hpp>
// For sf::Packet

#include <SFML/System.hpp>
// For sf::Vector2i

#include <vector>
// For std::vector


// ********************************************************************
// BOARD CLASS
// ********************************************************************

class Board {
public:
	// *** PUBLIC POSITION TYPE ***
	using pos_t = sf::Vector2i;

public:
	// *** BOARD SHIP DIRECTION AND LOCATION STATE ENUMS ***
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

public:
	// *** CONSTRUCTORS AND DESTRUCTOR ***
	Board();
	Board(sf::Packet & packet);
	~Board() = default;

	// *** NO COPY AND MOVE CONSTRUCTION AND ASSIGNMENT ***
	// A board cannot be copied nor moved (only passed by reference) 
	Board(const Board & board) = delete;
	Board(Board && board) = delete;
	Board & operator=(const Board & board) = delete;
	Board & operator=(Board && board) = delete;


public:
	// *** QUERY MEMBER FUNCTIONS ***
	Board::STATE get(pos_t position) const;
	bool areAllShipsDead() const;

	// *** MODIFIER MEMBER FUNCTIONS ***
	bool placeShip(pos_t position, int length, Board::DIR direction);
	bool shoot(pos_t position);


private:
	// *** PRIVATE HELPER FUNCTION ***
	void set(pos_t position, Board::STATE state);


private:
	// *** MEMBER VARIABLE ***
	std::vector<Board::STATE> _board;
};


// ********************************************************************
// PUBLIC HELPER FUNCTIONS
// ********************************************************************

bool positionIsValid(Board::pos_t position);

sf::Packet & operator<<(sf::Packet & packet, const Board & board);

sf::Packet & operator<<(sf::Packet & packet, const Board::pos_t & position);

sf::Packet & operator>>(sf::Packet & packet, Board::pos_t & position);

#endif // #ifndef FILE_BOARD_HPP_INCLUDED