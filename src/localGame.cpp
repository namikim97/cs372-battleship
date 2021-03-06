// localGame.cpp
//
// Created: 24 Feb 2019
// Updated: 03 MAr 2019
//
// Source for class LocalGame.

#include "localGame.hpp"

LocalGame::LocalGame(unsigned int height)
:	INITIAL_WIDTH{11*height/6},
	INITIAL_HEIGHT{height},
	BOARD_SIZE{(float) 2.f*height/3.f, (float) 2.f*height/3.f},
	LEFT_POSITION{(float) height/6.f,(float)  height/6.f},
	RIGHT_POSITION{(float) height,(float)  height/6.f},
	WINDOW_NAME{"Battleship"},
	_p1{},
	_p2{},
	_left{_p1, LEFT_POSITION, BOARD_SIZE},
	_right{_p2, RIGHT_POSITION, BOARD_SIZE},
	_window{sf::VideoMode{INITIAL_WIDTH, INITIAL_HEIGHT}, WINDOW_NAME},
	_state{P1_SETUP}
{ }

void LocalGame::run()
{
	#ifdef BATTLESHIP_SOUND
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

	bool enableSFX = false;
	sf::Sound hitSFX, missSFX;

	if(hitSoundEffectBuffer.loadFromFile("../assets/hit.wav") 
		&& missSoundEffectBuffer.loadFromFile("../assets/miss.wav"))
	{
		hitSFX.setBuffer(hitSoundEffectBuffer);
		missSFX.setBuffer(missSoundEffectBuffer);
		enableSFX = true;
	}
	#endif // #ifdef BATTLESHIP_SOUND

	sf::Time time;
	while (_window.isOpen())
	{
		processInput();
		update(time);

		#ifdef BATTLESHIP_SOUND
		if (enableSFX)
		{
			if(_soundEvent.playHitSFX)
			{
				_soundEvent.playHitSFX = false;
				hitSFX.play();
			}

			if(_soundEvent.playMissSFX)
			{
				_soundEvent.playMissSFX = false;
				hitSFX.play();
			}
		}
		#endif // #ifdef BATTLESHIP_SOUND

		render();
	}
}

// Created to resolve window-scaling issues
sf::Vector2i LocalGame::getRelativeToInitialPosition(sf::Vector2i position) const
{
	const auto WINDOW_SIZE = _window.getSize();
	position.x = (INITIAL_WIDTH * position.x) / WINDOW_SIZE.x;
	position.y = (INITIAL_HEIGHT * position.y) / WINDOW_SIZE.y;
	return position;
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
		auto relativePosition = getRelativeToInitialPosition(_mouse.position);
		leftBoardPosition = _left.getPositionOnBoard(relativePosition);
		rightBoardPosition = _right.getPositionOnBoard(relativePosition);
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
				if (_p2.get(rightBoardPosition) == Board::STATE::HIT)
				{
					_soundEvent.playHitSFX = true;
				}
				else // if (_p2.get(rightBoardPosition) == Board::STATE::MISS)
				{
					_soundEvent.playMissSFX = true;
				}

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
				if (_p1.get(leftBoardPosition) == Board::STATE::HIT)
				{
					_soundEvent.playHitSFX = true;
				}
				else // if (_p1.get(leftBoardPosition) == Board::STATE::MISS)
				{
					_soundEvent.playMissSFX = true;
				}

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

		// To resolve scaling issues, get relative to initial board:
		auto mousePosition = sf::Mouse().getPosition(_window);
		auto relativeMousePosition = getRelativeToInitialPosition(mousePosition);
		auto boardPosition = ref.getPositionOnBoard(relativeMousePosition);

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
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineColor(sf::Color::Red);
			circle.setOutlineThickness(1.f);
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
