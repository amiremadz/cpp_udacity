# CPPND: Capstone Snake Game 

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

## Modifications Made to Starter Repo to Fullfil Project Requiresments

### Basic Functionality Additions

<img src="annotated_gameplay.png"/>



<img src="annotated_terminal_output.png"/>

### Rubric Criteria Met (in additional to Required Rubric Points)

#### Loops, Functions, I/O

* The project demonstrates an understanding of C++ founctions and control structures: wall.cpp.

* The project accepts user input and processes the input: Lines 19 to 49 in main. 

#### Object Oriented Programming

* The project uses Object oriented Programming techniques: wall.cpp.

* Classes use appropriates access specifiers for class members: main.h.

* Class constructors utilize member initialization lists: Wall::Wall() in wall.cpp.

* Classes abstract implementation details from their interfaces: implementation of wall in game.cpp.

* Classes encapsulate behavior: class wall in wall.cpp

#### Memory management

* The project uses scope / RAII where appropriate: Objects such as unique_ptr moves in controller.cpp / .h utilize smart pointers to ensure proper allocation and deallocation of memory on the heap.

* The project uses smart pointers instead of raw pointers: Smart pointer - moves in controller.cpp / h

#### Concurrency

* The project uses multithreading: See member function MoveWall() in wall.cpp

* A mutex or lock is used in the project: See member function MoveWall() in wall.cpp












