// network_textGame.cpp
//
// Created: 22 Feb 2019
// Updated: 23 Feb 2019
//
// Source for LAN text-based Battleship game.

#include "network_textGame.hpp"
#include <unistd.h>
// ********************************************************************
// HELPER FUNCTIONS
// ********************************************************************

bool errorWhileConnectingToServer(sf::TcpSocket & socket, const sf::IpAddress & ipAddress)
{
	sf::TcpSocket::Status status = socket.connect(ipAddress.toString(), NETWORK_TEXTGAME_PORTNO);
	if (status != sf::TcpSocket::Done)
	{
	    std::cout << "Unable to connect to server..." << std::endl;
	    return true;
	}

	return false;
}

bool errorWhileWaitingForClient(sf::TcpSocket & socket)
{
	sf::TcpListener listener;

	// Bind the listener to a port
	if (listener.listen(NETWORK_TEXTGAME_PORTNO) != sf::TcpSocket::Done)
	{
		std::cout << "Unable to bind server listener to port..." << std::endl;
		std::cout << "Exiting..." << std::endl;
		return true;
	}

	// Accept a new connnection
	if (listener.accept(socket) != sf::TcpSocket::Done)
	{
		std::cout << "Unable to accept a new connection..." << std::endl;
		std::cout << "Exiting..." << std::endl;
		return true;
	}

	return false;
}


void client()
{
	std::cout << "Operating as a client..." << std::endl;
	std::cout << "Input a INET IP address to connect to, example input `123.4.5.67`: " << std::endl;

	auto strIPAddress = readToken();
	sf::IpAddress ipAddress(strIPAddress);
	if (ipAddress == sf::IpAddress::None)
	{
		std::cout << "The IP Address provided is invalid..." << std::endl;
		return;
	}

	sf::TcpSocket socket;
	if (errorWhileConnectingToServer(socket, ipAddress))
		return;


	Board clientBoard;
	placeShips(clientBoard);

	std::cout << "Waiting on the enemy..." << std::endl;
	sf::Packet serverBoardPacket;
	socket.receive(serverBoardPacket);
	Board serverBoard(serverBoardPacket);

	sf::Packet clientBoardPacket;
	clientBoardPacket << clientBoard;
	socket.send(clientBoardPacket);

	sf::Socket::Status status;
	bool clientTurn = false;
	do {
		Board::pos_t position;
		if (clientTurn)
		{
			sf::Packet turnPacket;
			position = playerTurn(clientBoard, serverBoard);
			turnPacket << position;

			printPlayerAndEnemy(clientBoard, serverBoard);

			std::cout << "Waiting on opponent..." << std::endl;
			status = socket.send(turnPacket);

			if (serverBoard.areAllShipsDead())
			{
				socket.disconnect();
				std::cout << "You won!" << std::endl;
				return;
			}
		}
		else
		{
			sf::Packet turnPacket;
			status = socket.receive(turnPacket);
			turnPacket >> position;

			clientBoard.shoot(position);

			if (clientBoard.areAllShipsDead())
			{
				socket.disconnect();
				std::cout << "Your opponent won!" << std::endl;
				return;
			}
		}


		position = {-1, 0};
		clientTurn = !clientTurn;

	} while (status != sf::Socket::Status::Disconnected);

	std::cout << "Socket disconnected..." << std::endl;
	std::cout << "Exiting..." << std::endl;
}


void server()
{
	std::cout << "Operating as a server...!" << std::endl;

	auto ipAddress = sf::IpAddress::getLocalAddress();
	if (ipAddress != sf::IpAddress::None)
	{
		std::cout << "Your IP Address is " << ipAddress.toString() << std::endl;
	}
	else
	{
		std::cout << "An error occured while getting you local IP Address. Exiting..." << std::endl;
		return;
	}

	sf::TcpSocket socket;
	std::cout << "Waiting for another player to join..." << std::endl;
	if (errorWhileWaitingForClient(socket))
		return;

	Board serverBoard;
	placeShips(serverBoard);

	sf::Packet serverBoardPacket;
	serverBoardPacket << serverBoard;
	socket.send(serverBoardPacket);

	std::cout << "Waiting on the enemy..." << std::endl;
	sf::Packet clientBoardPacket;
	socket.receive(clientBoardPacket);
	Board clientBoard(clientBoardPacket);

	sf::Socket::Status status;
	bool serverTurn = true;
	do {
		Board::pos_t position;
		if (serverTurn)
		{
			sf::Packet turnPacket;
			position = playerTurn(serverBoard, clientBoard);
			turnPacket << position;

			printPlayerAndEnemy(serverBoard, clientBoard);

			std::cout << "Waiting on opponent..." << std::endl;
			status = socket.send(turnPacket);

			if (clientBoard.areAllShipsDead())
			{
				socket.disconnect();
				std::cout << "You won!" << std::endl;
				return;
			}
		}
		else
		{
			sf::Packet turnPacket;
			status = socket.receive(turnPacket);
			turnPacket >> position;

			serverBoard.shoot(position);

			if (serverBoard.areAllShipsDead())
			{
				socket.disconnect();
				std::cout << "Your opponent won!" << std::endl;
				return;
			}
		}

		position = {-1, 0};
		serverTurn = !serverTurn;

	} while (status != sf::Socket::Status::Disconnected);

	std::cout << "Socket disconnected..." << std::endl;
	std::cout << "Exiting..." << std::endl;
}


// ********************************************************************
// PUBLIC FUNCTIONS
// ********************************************************************

void network_textGame()
{
	while (true)
	{
		std::cout << "Would you like to host or join a game?";
		std::cout << "\n(Operate as Server/client), input 'S/c': ";
		auto str = readToken();

		if (!str.empty())
		{
			switch (str[0])
			{
				case 'S':
				case 's':
				case 'H':
				case 'h':
					server();
					return;
				case 'C':
				case 'c':
				case 'J':
				case 'j':
					client();
					return;
				default:
					break;
			}
		}
	}
}
