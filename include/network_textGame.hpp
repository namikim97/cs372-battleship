// network_textGame.cpp
//
// Created: 22 Feb 2019
// Updated: 22 Feb 2019
//
// Header for LAN text-based Battleship game.


#ifndef FILE_NETWORK_TEXTGAME_HPP_INCLUDED
#define FILE_NETWORK_TEXTGAME_HPP_INCLUDED

const unsigned int NETWORK_TEXTGAME_PORTNO = 52311;

#include <SFML/Network.hpp>
// For sf::TcpSocket, sf::TcpListener, sf::Packet, etc.

#include <iostream>
// For std::cout, std::endl;

#include "board.hpp"
#include "textUtils.hpp"
#include "local_textGame.hpp"


// ********************************************************************
// PUBLIC FUNCTIONS
// ********************************************************************

void network_textGame();

#endif // #ifndef FILE_NETWORK_TEXTGAME_HPP_INCLUDED