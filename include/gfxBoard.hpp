// gfxBoard.hpp
//
// Created: 23 Feb 2019
// Updated: 25 Feb 2019
//
// Header for class GfxBoard.


#ifndef FILE_GFXBOARD_HPP_INCLUDED
#define FILE_GFXBOARD_HPP_INCLUDED

#include <SFML/System.hpp>
// For sf::Vector2f

#include <SFML/Graphics.hpp>
// For sf::Drawable, sf::Vertex

#include <vector>
// For std::vector

#include "board.hpp"

// ********************************************************************
// GFXBOARD CLASS
// ********************************************************************

class GfxBoard : public sf::Drawable
{

public:
	// *** CONSTRUCTORS AND DESTRUCTOR ***
	GfxBoard(const Board & board, sf::Vector2f position, sf::Vector2f size);
	~GfxBoard() = default;

	// *** NO COPY AND MOVE CONSTRUCTION AND ASSIGNMENT ***
	// A board cannot be copied nor moved (only passed by reference) 
	GfxBoard(const GfxBoard & gfxboard) = delete;
	GfxBoard(GfxBoard && gfxboard) = delete;
	GfxBoard & operator=(const GfxBoard & gfxboard) = delete;
	GfxBoard & operator=(GfxBoard && gfxboard) = delete;

public:
	// *** QUERY MEMBER FUNCTIONS ***
	Board::pos_t getPositionOnBoard(sf::Vector2i mousePosition) const;
	sf::Vector2f getDrawPosition(Board::pos_t position) const;
	float getCircleRadius() const;

public:
	// *** MODIFIER MEMBER FUNCTIONS ***
	void enableShowShips();
	void disableShowShips();

private:
	// *** DRAWABLE ***
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	// *** MEMBER VARIABLES ***
	const Board & _board;
	std::vector<sf::Vertex> _lines;
	sf::Vector2f _position, _size;
	bool _showShips;
};




#endif // #ifndef FILE_GFXBOARD_HPP_INCLUDED