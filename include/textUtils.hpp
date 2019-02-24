// textUtils.hpp
//
// Created: 22 Feb 2019
// Updated: 23 Feb 2019
//
// Header for some text-based utilities.

#ifndef FILE_TEXTUTILS_HPP_INCLUDED
#define FILE_TEXTUTILS_HPP_INCLUDED

#include <iostream>
// For std::cin, std::cout, std::endl
#include <limits>
// For std::numeric_limits<std::streamsize>::max()
#include <algorithm>
// For std::transform
#include <string>
// For std::string, std::tolower, std::toupper

#include "board.hpp"


// ********************************************************************
// PUBLIC FUNCTIONS
// ********************************************************************

// Alias to std:cin.ignore(<max stream limit>)
void flush_cin();

// Prints a text-based version of the board
// By default, showAll ships is false
void print(const Board & board, bool showAll = false);

// Wrapper for std::cin to read a string input.
// Returns an empty string on a failed parse.
std::string readToken();

// Returns whether the string starts with a D/d or R/r.
// Used to verify a string is parseable as a Board::DIR.
bool isParseableShipDirection(const std::string & strDirection);

// Call isParseableShipDirection() first to verify strDirection is
// parseable to either Board::DIR::DOWN or Board::DIR::RIGHT.
Board::DIR parseShipDirection(const std::string & strDirection);

// Using std::cin, get a Board::pos_t
Board::pos_t getPositionFromUser();

std::string & str_tolower(std::string & s);

std::string & str_toupper(std::string & s);

#endif // #ifndef FILE_TEXTUTILS_HPP_INCLUDED