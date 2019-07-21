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
#include <vector>

// A Ship can be either horizontal or vertical
// The occupied cells are extrapolated from an origin and a Direction
enum Direction {Left, Right};
enum GameState {Firing, GameOver, Placement};
enum ShipClass {AircraftCarrier, Battleship, Cruiser, Destroyer, UBoat};


// human-displaying the ShipClass enum
std::string shipClassString(ShipClass sc);
char shipClassChar(ShipClass sc);
int shipLength(ShipClass sc);

// string vector alias
typedef std::vector<std::string> lines;

#endif