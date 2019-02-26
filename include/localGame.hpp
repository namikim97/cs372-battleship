// localGame.hpp
//
// Created: 24 Feb 2019
// Updated: 25 Feb 2019
//
// Header for class LocalGame.

#ifndef FILE_LOCALGAME_HPP_INCLUDED
#define FILE_LOCALGAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
// For sf::RenderWindow, sf::Vector2f, sf::Event, etc
#include <SFML/Audio.hpp>
// For sf::SoundBuffer

#include <map>

#include "board.hpp"
#include "gfxBoard.hpp"


// ********************************************************************
// LOCALGAME CLASS
// ********************************************************************

class LocalGame
{
private:
	// *** GAME PARAMETERS ***
	const std::vector<int> SHIP_LENGTHS{ 2, 3, 3, 4, 5 };

	const unsigned int WIDTH, HEIGHT;
	const sf::Vector2f BOARD_SIZE, LEFT_POSITION, RIGHT_POSITION;
	const std::string WINDOW_NAME;

private:

	// *** PLAY SOUND EFFECT ***
	struct SoundEffectEvent {
		bool playHit = false;
		bool playMiss = false;
	} _sound;

	// *** PROCESS INPUT VARIABLES ***
	struct Mouse {
		bool leftButtonPressed;
		bool rightButtonPressed;
		sf::Vector2i position;
	} _mouse;

	// *** SETUP VALUES ***
	struct Setup {
		std::size_t shipNumber = 0;
		Board::DIR direction = Board::DIR::DOWN;
	} _setup;

private:
	// *** GAME STATES ***
	enum STATE {
		P1_SETUP,
		P2_SETUP,
		P1_TURN,
		P2_TURN
	};

public:
	// *** CONSTRUCTOR AND DESTRUCTOR ***
	LocalGame();
	~LocalGame() = default;

	// *** NO COPY AND MOVE CONSTRUCTION AND ASSIGNMENT ***
	// A LocalGame cannot be copied nor moved (only passed by reference) 
	LocalGame(const LocalGame & localGame) = delete;
	LocalGame(LocalGame && localGame) = delete;
	LocalGame & operator=(const LocalGame & localGame) = delete;
	LocalGame & operator=(LocalGame && localGame) = delete;

public:
	// *** PUBLIC RUN GAME MEMBER FUNCTION *** 
	void run();

private:
	// *** PRIVATE MODIFIER MEMBER FUNCTIONS ***
	void processInput();
	void update(sf::Time time);
	void render();

public:
	// *** MEMBER VARIABLES ***
	// Order matters here for Board and GfxBoard
	Board _p1, _p2;
	GfxBoard _left, _right;
	sf::RenderWindow _window;
	LocalGame::STATE _state;
};

#endif // #ifndef FILE_LOCALGAME_HPP_INCLUDED
