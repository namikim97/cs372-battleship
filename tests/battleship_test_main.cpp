// battleship_test_main.cpp
// Original Author: Glenn G. Chappell
// Modified by: Charles Emerson
//
// Created: 10 Feb 2019 (from da6_test_main.cpp)
// Updated: 10 Feb 2019
//
// For CS 372 Spring 2019
// Tests for Project 1 Battleship game components: main program.
// Uses the "Catch" unit-testing framework, version 2
// Requires are defined in battleship_test_suites.cpp.

#define CATCH_CONFIG_FAST_COMPILE
                             // Disable some features for faster compile
#define CATCH_CONFIG_RUNNER  // We write our own main
#include "catch.hpp"         // For the "Catch" unit-testing framework
#include <iostream>          // For std::cout, endl, cin


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    while (std::cin.get() != '\n') ;
}


// Main program
// Run all tests. Prompt for ENTER before exiting.
int main(int argc,
         char *argv[])
{
    const std::string tname = "Battleship"
                              " - CS 372 Project 1";
                             // Printable name for this test suite
    Catch::Session session;  // Primary Catch object
    int catchresult;         // Catch return code; for return by main

    // Handle command line
    catchresult = session.applyCommandLine(argc, argv);

    if (!catchresult)  // Continue only if no command-line error
    {
        // Run test suites
        std::cout << "BEGIN tests for "
                  << tname << std::endl << std::endl;
        catchresult = session.run();
        std::cout << "END tests for "
                  << tname << std::endl << std::endl;
    }

    // Wait for user
    std::cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from Catch
    return catchresult;
}