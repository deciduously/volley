/*
* ship.h
* Represents a single ship on the battleship game board
* Benjamin Lovy
 */
#ifndef __SHIP_H_INCLUDED
#define __SHIP_H_INCLUDED

#include "util.h"

// TODO typedef struct shipPlacement

class Ship
{
    Cell origin;
    Direction direction;
    int hits;
    ShipClass shipClass;

public:
    Ship(Cell o, ShipClass sc, Direction d);
    std::vector<Cell> containedCells();
    ShipClass getShipClass();
};
#endif