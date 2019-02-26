// localGame.cpp
//
// Created: 24 Feb 2019
// Updated: 25 Feb 2019
//
// Source for class LocalGame.

#include "localGame.hpp"

// ********************************************************************
// HELPER FUNCTIONS
// ********************************************************************

// *** CONSTRUCTOR AND DESTRUCTOR ***
LocalGame::LocalGame()
:	WIDTH{1100/2},
	HEIGHT{600/2},
	BOARD_SIZE{400.f/2, 400.f/2},
	LEFT_POSITION{100.f/2, 100.f/2},
	RIGHT_POSITION{600.f/2, 100.f/2},
	WINDOW_NAME{"Battleship"},
	_p1{},
	_p2{},
	_left{_p1, LEFT_POSITION, BOARD_SIZE},
	_right{_p2, RIGHT_POSITION, BOARD_SIZE},
	_window{sf::VideoMode{WIDTH, HEIGHT}, WINDOW_NAME},
	_state(P1_SETUP)
{ }

void LocalGame::run()
{
	sf::SoundBuffer musicBuffer;
	sf::SoundBuffer hitSoundEffectBuffer;
	sf::SoundBuffer missSoundEffectBuffer;
	sf::Sound music;

	if(musicBuffer.loadFromFile("../assets/music.wav"))
	{
		music.setBuffer(musicBuffer);
		music.setLoop(true);

		music.play();
	}

	bool allowSoundEffects = false;

	sf::Sound hit;
	sf::Sound miss;

	if(hitSoundEffectBuffer.loadFromFile("../assets/hit.wav") 
		&& missSoundEffectBuffer.loadFromFile("../assets/miss.wav"))
	{
		hit.setBuffer(hitSoundEffectBuffer);
		miss.setBuffer(missSoundEffectBuffer);
		allowSoundEffects = true;
	}


	sf::Time time;
	while (_window.isOpen())
	{
		processInput();
		update(time);

		if(_sound.playHit)
		{
			_sound.playHit = false;
			hit.play();
		}

		render();
	}

}

// *** MODIFIER MEMBER FUNCTIONS ***
void LocalGame::processInput()
{
	_mouse.leftButtonPressed = false;
	_mouse.rightButtonPressed = false;
	_mouse.position = {-1, -1};

	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
			return;
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			switch (event.mouseButton.button)
			{
				default:
					break;
				case sf::Mouse::Button::Left:
					_mouse.leftButtonPressed = true;
					_mouse.position = {event.mouseButton.x, event.mouseButton.y};
					break;
				case sf::Mouse::Button::Right:
					_mouse.rightButtonPressed = true;
					_mouse.position = {event.mouseButton.x, event.mouseButton.y};
					break;
			}
		}
	}
}

void LocalGame::update(sf::Time time)
{
	(void) time; // @TODO

	sf::Vector2i leftBoardPosition = {-1, -1};
	sf::Vector2i rightBoardPosition = {-1, -1};

	if (_mouse.leftButtonPressed)
	{
		leftBoardPosition = _left.getPositionOnBoard(_mouse.position);
		rightBoardPosition = _right.getPositionOnBoard(_mouse.position);
	}

	switch (_state)
	{
		case P1_SETUP:
			if (_mouse.rightButtonPressed)
				_setup.direction = (_setup.direction == Board::DIR::DOWN)? Board::DIR::RIGHT : Board::DIR::DOWN;

			if (_p1.placeShip(leftBoardPosition, SHIP_LENGTHS[_setup.shipNumber], _setup.direction))
			{
				++_setup.shipNumber;

				if (_setup.shipNumber == SHIP_LENGTHS.size())
				{
					_setup.shipNumber = 0;
					_setup.direction = Board::DIR::DOWN;
					_state = P2_SETUP;

					_right.enableShowShips();
					_left.disableShowShips();
				}
			}
			break;
		case P2_SETUP:
			if (_mouse.rightButtonPressed)
				_setup.direction = (_setup.direction == Board::DIR::DOWN)? Board::DIR::RIGHT : Board::DIR::DOWN;

			if (_p2.placeShip(rightBoardPosition, SHIP_LENGTHS[_setup.shipNumber], _setup.direction))
			{
				++_setup.shipNumber;

				if (_setup.shipNumber == SHIP_LENGTHS.size())
				{
					_state = P1_TURN;

					_left.enableShowShips();
					_right.disableShowShips();
				}
			}
			break;
		case P1_TURN:
			if (_p2.shoot(rightBoardPosition))
			{
				_sound.playHit = true;
				_state = P2_TURN;

				_right.enableShowShips();
				_left.disableShowShips();

				if (_p2.areAllShipsDead())
				{
					printf("P1 Won!\n"); // @REMOVE
					_window.close();
					return;
				}
			}
			break;
		case P2_TURN:
			if (_p1.shoot(leftBoardPosition))
			{
				_sound.playHit = true;
				_state = P1_TURN;

				_left.enableShowShips();
				_right.disableShowShips();

				if (_p1.areAllShipsDead())
				{
					printf("P2 Won!\n"); // @REMOVE
					_window.close();
					return;
				}
			}
			break;
	}
}

void LocalGame::render()
{
	_window.clear(sf::Color::Black);

	_window.draw(_left);
	_window.draw(_right);

	if (_state == P1_SETUP || _state == P2_SETUP)
	{
		const GfxBoard & ref = (_state == P1_SETUP)? _left : _right;

		auto mousePosition = sf::Mouse().getPosition(_window);
		auto boardPosition = ref.getPositionOnBoard(mousePosition);

		auto length = SHIP_LENGTHS[_setup.shipNumber];
		Board::pos_t endPosition;
		if (_setup.direction == Board::DIR::DOWN)
		{
			endPosition = {boardPosition.x, boardPosition.y + length - 1};
		}
		else
		{
			endPosition = {boardPosition.x + length - 1, boardPosition.y};
		}
		
		if (positionIsValid(boardPosition) && positionIsValid(endPosition))
		{
			auto length = SHIP_LENGTHS[_setup.shipNumber];

			auto x = boardPosition.x;
			auto y = boardPosition.y;

			sf::CircleShape circle{ref.getCircleRadius(), 100};
			switch (_setup.direction)
			{
				case Board::DIR::DOWN:
					for (auto j = y; j < y + length ; ++j)
					{
						circle.setPosition(ref.getDrawPosition({x, j}));
						_window.draw(circle);
					}
					break;
				case Board::DIR::RIGHT:
					for (auto i = x; i < x + length ; ++i)
					{
						circle.setPosition(ref.getDrawPosition({i, y}));
						_window.draw(circle);
					}
					break;
			}
		}
	}

	_window.display();
}
