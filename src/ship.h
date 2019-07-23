/*
* ship.h
* Represents a single ship on the battleship game board
* Benjamin Lovy
 */
#ifndef __SHIP_H_INCLUDED
#define __SHIP_H_INCLUDED

#include <tuple>

#include "util.h"

class Ship
{
    std::tuple<int, int> origin;
    Direction direction;
    int hits;
    ShipClass shipClass;

public:
    Ship(int row, int col, Direction dir, ShipClass sc);
};
#endif