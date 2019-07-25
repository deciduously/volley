/* 
* util.h
* Various enums and functions that don't belong to a particular class
* TODO should this actually be a class?  like a singleton?  what's a singleton?
* Asking the big questions
* Benjamin Lovy
*/
#ifndef __UTIL_H_INCLUDED
#define __UTIL_H_INCLUDED

#include <string>
#include <tuple>
#include <vector>

// Board size is fixed
const int BOARD_SIZE = 10;

// A Ship can be either horizontal or vertical
// The occupied cells are extrapolated from an origin and a Direction
enum Direction
{
    Left,
    Right
};
enum GameState
{
    Firing,
    GameOver,
    Placement
};

// string vector alias
typedef std::vector<std::string> lines;

// origin tuple alias {row, col}
typedef std::tuple<int, char> cell;

#endif