// gfxBoard.cpp
//
// Created: 23 Feb 2019
// Updated: 25 Feb 2019
//
// Source for class GfxBoard.

#include "gfxBoard.hpp"


// ********************************************************************
// GFXBOARD CLASS
// ********************************************************************

// *** CONSTRUCTORS AND DESTRUCTOR ***
GfxBoard::GfxBoard(const Board & board, sf::Vector2f position, sf::Vector2f size)
:	_board(board),
	_lines(44),
	_position(position),
	_size(size),
	_showShips(true)
{
	auto x_offset = position.x, y_offset = position.y;
	for (auto j = 0; j <= 10; ++j)
	{
		_lines[2*j] = sf::Vertex(sf::Vector2f(0.f + x_offset, (size.y/10.f)*j + y_offset));
		_lines[2*j+1] = sf::Vertex(sf::Vector2f(size.x + x_offset, (size.x/10.f)*j + y_offset));
	}

	for (auto i = 0; i <= 10; ++i)
	{
		_lines[2*i+22] = sf::Vertex(sf::Vector2f((size.x/10.f)*i+x_offset, 0.f + y_offset));
		_lines[2*i+23] = sf::Vertex(sf::Vector2f((size.x/10.f)*i+x_offset, size.y + y_offset));
	}
}

void GfxBoard::enableShowShips()
{
	_showShips = true;
}

void GfxBoard::disableShowShips()
{
	_showShips = false;
}

Board::pos_t GfxBoard::getPositionOnBoard(sf::Vector2i mousePosition) const
{
	mousePosition.x -= (int) _position.x;
	mousePosition.y -= (int) _position.y;

	const auto XMULTIPLIER = (_size.x/10.f);
	const auto YMULTIPLIER = (_size.y/10.f);

	mousePosition.x /= XMULTIPLIER;
	mousePosition.y /= YMULTIPLIER;

	return {mousePosition.x, mousePosition.y};
}

float GfxBoard::getCircleRadius() const
{
	const auto RADIUS = _size.x/(10.f*2.f*1.2f);
	return RADIUS;
}

sf::Vector2f GfxBoard::getDrawPosition(Board::pos_t pos) const
{
	const auto RADIUS = getCircleRadius();
	const auto XOFFSET = _position.x + _size.x/20.f - RADIUS;
	const auto YOFFSET = _position.y + _size.y/20.f - RADIUS;
	const auto XMULTIPLIER = _size.x/10.f;
	const auto YMULTIPLIER = _size.y/10.f;

	return {XOFFSET + pos.x*XMULTIPLIER, YOFFSET + pos.y*YMULTIPLIER};
}

void GfxBoard::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(&(_lines[0]), _lines.size(), sf::Lines);

	const auto RADIUS = getCircleRadius();
	sf::CircleShape circle(RADIUS, 100);
	for (auto j = 0; j < 10; ++j)
	{
		for (auto i = 0; i < 10; ++i)
		{
			auto state = _board.get({i, j});

			if (state == Board::STATE::EMPTY)
				continue;

			if (!_showShips && state == Board::STATE::SHIP)
				continue;

			circle.setPosition(getDrawPosition({i, j}));

			switch (state)
			{
				default: // To kill warning, EMPTY handled above
					continue;
				case Board::STATE::SHIP:
					circle.setFillColor(sf::Color::White);
					break;
				case Board::STATE::MISS:
					circle.setFillColor(sf::Color::Blue);
					break;
				case Board::STATE::HIT:
					circle.setFillColor(sf::Color::Red);
					break;
			}

			target.draw(circle);
		}
	}
}