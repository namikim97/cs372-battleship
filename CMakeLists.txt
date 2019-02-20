# CMakeLists.txt
# Author: Charles Emerson
#
# Created: 8 Feb 2019
# Updated: 18 Feb 2019
# 
# Created from the CMake configuration for SFML at:
# https://github.com/SFML/SFML/wiki/Tutorial%3A-Build-your-SFML-project-with-CMake


########################################################################
# Setup
########################################################################
cmake_minimum_required(VERSION 2.6)

project(cs372-battleship)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wall -O3")
include_directories("include")


########################################################################
# Main executable (main.out)
########################################################################
set(SOURCE_MAIN
  src/main.cpp
)

set(SOURCE_FILES
  src/board.cpp
  src/textBasedGame.cpp
)

# Define sources and executable
set(EXECUTABLE_NAME battleship.out)
add_executable(${EXECUTABLE_NAME} ${SOURCE_MAIN} ${SOURCE_FILES})


########################################################################
# Testing executable (catch_tests.out)
########################################################################
set(TEST_SOURCE_FILES
    tests/battleship_test_main.cpp
    tests/battleship_test_suites.cpp
    ${SOURCE_FILES}
)

# Define sources and executable
set(TEST_EXECUTABLE_NAME catch_tests.out)
add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES})


########################################################################
# Find SFML
########################################################################
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML

#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
include(CPack)
