# Battleship (CS 372 Partner Project)
Nami Kim and Charles Emerson


### Introduction
This project uses [SFML](https://www.sfml-dev.org/) and [Catch2](https://github.com/catchorg/Catch2).


### Steps to compile
(This method requires CMake 2.6 or later and SFML 2.4.2 or later to be installed)

1. Create a new folder in the project folder called `build`
2. Navigate into `build`
3. `cmake ..`
4. `make`
5. Run the `./battleship.out` game with an argument of `sfml`, `local`, or `network`

The game is capable of playing music and sound effects. To enable sound:
1. Uncomment the line `add_definitions( -DBATTLESHIP_SOUND )` located in `CMakeLists.txt`
2. Add a folder `assets` in the project folder
3. Add a `music.wav` in the `assets` folder for looping background music
4. Add a `hit.wav` in the `assets` folder for a sound effect on hit
5. Add a `miss.wav` in the `assets` folder for a sound effect on miss

### Specific Game Types:
1. Local Text-Based Game (No networking), run `./battleship.out l` or `./battleship.out local-text`
2. Networked Text-Based Game (Networking), run `./battleship.out n` or `./battleship.out network-text`
3. Local Graphics-Based Game (No networking), run `./battleship.out s` or `./battleship sfml`

### Steps to compile and run the testing framework
(This method requires CMake 2.6 or later to be installed)

1. Download the Catch2 single-header [catch.hpp](https://github.com/catchorg/Catch2/releases/download/v2.6.1/catch.hpp) into the folder `include`
2. Create a new folder in the project folder called `build` (If not already created)
3. Navigate into `build`.
4. `cmake ..`
5. `make`
6. Run `./main.out`
