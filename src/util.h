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

enum Direction {Left, Right};
enum GameState {Firing, GameOver, Placement};
enum ShipClass {AircraftCarrier = 5, Battleship = 4, Cruiser = 3, Destroyer = 2, UBoat = 3};

std::string shipClassLongName(ShipClass sc);

// TODO should this return a character instead?
std::string shipClassLetter(ShipClass sc);

#endif