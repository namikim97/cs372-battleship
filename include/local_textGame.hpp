// local_textGame.hpp
//
// Created: 18 Feb 2019
// Updated: 22 Feb 2019
//
// Header for simple text-based Battleship

#ifndef FILE_LOCAL_TEXTGAME_HPP_INCLUDED
#define FILE_LOCAL_TEXTGAME_HPP_INCLUDED

#include <iostream>
// For std::cout, std::endl;

#include "board.hpp"
#include "textUtils.hpp"


// ********************************************************************
// PUBLIC FUNCTIONS
// ********************************************************************

void promptForShipDirectionAndPosition(int length);

void promptToShootPosition();

void placeShips(Board & board);

void printPlayerAndEnemy(const Board & player, const Board & enemy);

//Returns the position shot. Returns (-1, -1) upon a winning shot.
Board::pos_t playerTurn(const Board & player, Board & enemy);

void local_textGame();

#endif // #ifndef FILE_LOCAL_TEXTGAME_HPP_INCLUDED
