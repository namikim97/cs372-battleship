// battleship_test_suites.cpp
// Original Author: Glenn G. Chappell
// Modified by: Charles Emerson
//
// Created: 10 Feb 2019 (from da6_test_suites.cpp)
// Updated: 10 Feb 2019
//
// For CS 372 Spring 2019
// Tests for Project 1 Battleship game components: test suites.
// Uses the "Catch" unit-testing framework, version 2

// Includes for code to be tested
#include "board.hpp"

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <vector>
#include <utility>

// *****************************************************
// *** HELPER FUNCTIONS FOR THE TEST PROGRAM ***
// *****************************************************


bool placeShip_DOWN(Board & board, int pos_x, int pos_y, int length)
{
	return board.placeShip(pos_x, pos_y, length, Board::DIR::DOWN);
}

bool placeShip_RIGHT(Board & board, int pos_x, int pos_y, int length)
{
	return board.placeShip(pos_x, pos_y, length, Board::DIR::RIGHT);
}

bool shoot(Board & board, int pos_x, int pos_y)
{
	return board.shootLocation(pos_x, pos_y);
}

bool checkBoardPositions(
	const Board & board, 
	std::vector<std::pair<int, int>> positions, 
	Board::STATE state)
{
	for(const auto & pos : positions)
	{
		if (board.getStatus(pos.first, pos.second) != state)
		{
			return false;
		}
	}
	return true;
}

int checkBoardOccurences(const Board & board, Board::STATE state)
{
	int count = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (board.getStatus(i, j) == state)
			{
				++count;
			}
		}
	}
	return count;
}

std::vector<std::pair<int, int>> getPositionsBetween(
    std::pair<int, int> start, std::pair<int, int> end)
{
    std::vector<std::pair<int, int>> positions;

    if (start.first == end.first && end.second >= start.second)
    {
        for (int i = start.second; i <= end.second; ++i)
        {
            positions.emplace_back(start.first, i);
        }
    } else if (start.second == end.second && end.first >= start.first)
    {
        for (int i = start.first; i <= end.first; ++i)
        {
            positions.emplace_back(i, start.second);
        }
    } else {
        throw "!!! Malformed test in Testing Framework. !!!";
    }

    return positions;
}


// *****************************************************
// *** TEST FUNCTIONS FOR THE TEST PROGRAM ***
// *****************************************************


void test_andPlaceShip_DOWN(Board & board, int pos_x, int pos_y, int length)
{
	INFO( "Place a length " << length << " ship DOWN at (" << pos_x << ", " << pos_y << ") is successful" );
	REQUIRE( placeShip_DOWN(board, pos_x, pos_y, length) );
}

void test_andPlaceShip_RIGHT(Board & board, int pos_x, int pos_y, int length)
{
	INFO( "Place a length " << length << " ship RIGHT at (" << pos_x << ", " << pos_y << ") is successful" );
	REQUIRE( placeShip_RIGHT(board, pos_x, pos_y, length) );
}

void test_placeShip_Fails_DOWN(Board & board, int pos_x, int pos_y, int length)
{
	INFO( "Place a length " << length << " ship DOWN at (" << pos_x << ", " << pos_y << ") is NOT successful" );
	REQUIRE_FALSE( placeShip_DOWN(board, pos_x, pos_y, length) );
}

void test_placeShip_Fails_RIGHT(Board & board, int pos_x, int pos_y, int length)
{
	INFO( "Place a length " << length << " ship RIGHT at (" << pos_x << ", " << pos_y << ") is NOT successful" );
	REQUIRE_FALSE( placeShip_RIGHT(board, pos_x, pos_y, length) );
}

void test_andShoot(Board & board, int pos_x, int pos_y)
{
	INFO( "Check shot at (" << pos_x << ", " << pos_y << ") is successful" );
	REQUIRE( shoot(board, pos_x, pos_y) );
}


void test_shoot_Fails(Board & board, int pos_x, int pos_y)
{
	INFO( "Check shot at (" << pos_x << ", " << pos_y << ") is NOT successful" );
	REQUIRE_FALSE( shoot(board, pos_x, pos_y) );
}


void test_numEMPTY_equals(const Board & board, int num)
{
	INFO ( "Check count of EMPTY position is " << num );
	REQUIRE(checkBoardOccurences(board, Board::STATE::EMPTY) == num);
}

void test_numSHIP_equals(const Board & board, int num)
{
	INFO ( "Check count of SHIP position is " << num );
	REQUIRE(checkBoardOccurences(board, Board::STATE::SHIP) == num);
}

void test_numMISS_equals(const Board & board, int num)
{
	INFO ( "Check count of MISS position is " << num );
	REQUIRE(checkBoardOccurences(board, Board::STATE::MISS) == num);
}

void test_numHIT_equals(const Board & board, int num)
{
	INFO ( "Check count of HIT position is " << num );
	REQUIRE(checkBoardOccurences(board, Board::STATE::HIT) == num);
}

void test_positionsBetweenAre_EMPTY(const Board & board,
    std::pair<int, int> start, std::pair<int, int> end)
{
    INFO( "Check positions between (" << start.first << ","
        << start.second << ") and (" << end.first << ","
        << end.second << ") are EMPTY" );
    REQUIRE(checkBoardPositions(board,
        getPositionsBetween(start, end), Board::STATE::EMPTY));
}

void test_positionsBetweenAre_SHIP(const Board & board,
    std::pair<int, int> start, std::pair<int, int> end)
{
    INFO( "Check positions between (" << start.first << ","
        << start.second << ") and (" << end.first << ","
        << end.second << ") are SHIP" );
    REQUIRE(checkBoardPositions(board,
        getPositionsBetween(start, end), Board::STATE::SHIP));
}

void test_positionsBetweenAre_MISS(const Board & board,
    std::pair<int, int> start, std::pair<int, int> end)
{
    INFO( "Check positions between (" << start.first << ","
        << start.second << ") and (" << end.first << ","
        << end.second << ") are MISS" );
    REQUIRE(checkBoardPositions(board,
        getPositionsBetween(start, end), Board::STATE::MISS));
}

void test_positionsBetweenAre_HIT(const Board & board,
    std::pair<int, int> start, std::pair<int, int> end)
{
    INFO( "Check positions between (" << start.first << ","
        << start.second << ") and (" << end.first << ","
        << end.second << ") are HIT" );
    REQUIRE(checkBoardPositions(board,
        getPositionsBetween(start, end), Board::STATE::HIT));
}


// *****************************************************
// *** TEST CASES FOR THE TEST PROGRAM ***
// *****************************************************

TEST_CASE( "Board class - Ship Placements", "[Board][PlaceShips]" )
{
	Board board;
	SECTION( "Empty Board" )
	{
		test_numEMPTY_equals(board, 100);
		test_numSHIP_equals(board, 0);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
	}

	SECTION( "Place a length 3 ship: (0,0)/DOWN/3" )
	{
		test_andPlaceShip_DOWN(board, 0, 0, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {0,0}, {0,2});
	}

	SECTION( "Place a length 5 ship: (5,5)/DOWN/5" )
	{
		test_andPlaceShip_DOWN(board, 5, 5, 5);
		test_numEMPTY_equals(board, 95);
		test_numSHIP_equals(board, 5);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {5,5}, {5,9});
	}

	SECTION( "Place a length 3 ship: (0,0)/RIGHT/3" )
	{
		test_andPlaceShip_RIGHT(board, 0, 0, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {0,0}, {2,0});
	}

	SECTION( "Place a length 5 ship: (5,5)/DOWN/5" )
	{
		test_andPlaceShip_RIGHT(board, 5, 5, 5);
		test_numEMPTY_equals(board, 95);
		test_numSHIP_equals(board, 5);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {5,5}, {9,5});
	}

	SECTION( "Cannot place a ship on a ship: (0,0)/DOWN/3, (0,0)/RIGHT/3" )
	{
		test_andPlaceShip_DOWN(board, 0, 0, 3);
		test_placeShip_Fails_RIGHT(board, 0, 0, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {0,0}, {0,2});
	}

	SECTION( "Cannot place a ship on a ship: (0,0)/DOWN/3, (0,1)/RIGHT/3" )
	{
		test_andPlaceShip_DOWN(board, 0, 0, 3);
		test_placeShip_Fails_RIGHT(board, 0, 1, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {0,0}, {0,2});
	}

	SECTION( "Cannot place a ship on a ship: (0,0)/DOWN/3, (0,0)/DOWN/3" )
	{
		test_andPlaceShip_DOWN(board, 0, 0, 3);
		test_placeShip_Fails_DOWN(board, 0, 0, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {0,0}, {0,2});
	}

	SECTION( "Cannot place a ship on a ship: (0,0)/DOWN/3, (0,1)/DOWN/3" )
	{
		test_andPlaceShip_DOWN(board, 0, 0, 3);
		test_placeShip_Fails_DOWN(board, 0, 1, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {0,0}, {0,2});
	}

	SECTION( "Cannot place a ship on a ship: (4,4)/DOWN/3, (3,5)/RIGHT/3" )
	{
		test_andPlaceShip_DOWN(board, 4, 4, 3);
		test_placeShip_Fails_RIGHT(board, 3, 5, 3);
		test_placeShip_Fails_DOWN(board, 4, 4, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {4,4}, {4,6});
	}

	SECTION( "Cannot place a ship on a ship: (4,4)/RIGHT/3, (5,3)/DOWN/3" )
	{
		test_andPlaceShip_RIGHT(board, 4, 4, 3);
		test_placeShip_Fails_DOWN(board, 5, 3, 3);
		test_placeShip_Fails_RIGHT(board, 4, 4, 3);
		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 3);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
		test_positionsBetweenAre_SHIP(board, {4,4}, {6,4});
	}

	SECTION( "Cannot place ships outside" )
	{
		test_placeShip_Fails_RIGHT(board, 10, 12, 3);
		test_placeShip_Fails_RIGHT(board, 8, 9, 3);
		test_placeShip_Fails_RIGHT(board, 100000, 0, 3);
		test_placeShip_Fails_RIGHT(board, -1, 0, 3);
		test_placeShip_Fails_RIGHT(board, 0, -1, 3);
		test_placeShip_Fails_RIGHT(board, 9, 17, 3);
		test_placeShip_Fails_RIGHT(board, 12, 20, 3);
		test_placeShip_Fails_DOWN(board, 10, 12, 3);
		test_placeShip_Fails_DOWN(board, 9, 8, 3);
		test_placeShip_Fails_DOWN(board, 100000, 0, 3);
		test_placeShip_Fails_DOWN(board, -1, 0, 3);
		test_placeShip_Fails_DOWN(board, 0, -1, 3);
		test_placeShip_Fails_DOWN(board, 9, 17, 3);
		test_placeShip_Fails_DOWN(board, 12, 20, 3);

		test_numEMPTY_equals(board, 100);
		test_numSHIP_equals(board, 0);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 0);
	}

}


TEST_CASE( "Board class - Shooting", "[Board][Shoot]" )
{
	Board board;
	SECTION( "Shoot an Empty Board" )
	{
		test_andShoot(board, 1, 1);
		test_shoot_Fails(board, 1, 1);

		test_numEMPTY_equals(board, 99);
		test_numSHIP_equals(board, 0);
		test_numMISS_equals(board, 1);
		test_numHIT_equals(board, 0);

		test_positionsBetweenAre_MISS(board, {1, 1}, {1,1});
	}

	SECTION( "Cannot shoot outside board" )
	{
		test_shoot_Fails(board, 10, 12);
		test_shoot_Fails(board, 100000, 0);
		test_shoot_Fails(board, -1, 0);
		test_shoot_Fails(board, 0, -1);
		test_shoot_Fails(board, 9, 17);
		test_shoot_Fails(board, 12, 20);
		test_shoot_Fails(board, 10, 12);
		test_shoot_Fails(board, 100000, 0);
		test_shoot_Fails(board, -1, 0);
		test_shoot_Fails(board, 0, -1);
		test_shoot_Fails(board, 9, 17);
		test_shoot_Fails(board, 12, 20);
	}

	SECTION( "Shoot a ship" )
	{
		test_andPlaceShip_DOWN(board, 0, 0, 3);
		test_andShoot(board, 0, 0);

		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 2);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 1);

		test_shoot_Fails(board, 0, 0);

		test_positionsBetweenAre_SHIP(board, {0, 1}, {0,2});

		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 2);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 1);

		test_andShoot(board, 0, 1);

		test_numEMPTY_equals(board, 97);
		test_numSHIP_equals(board, 1);
		test_numMISS_equals(board, 0);
		test_numHIT_equals(board, 2);

		test_andShoot(board, 1, 1);

		test_numEMPTY_equals(board, 96);
		test_numSHIP_equals(board, 1);
		test_numMISS_equals(board, 1);
		test_numHIT_equals(board, 2);
	}
}
