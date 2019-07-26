/*
* ship.h
* Represents a single ship on the battleship game board
* Benjamin Lovy
 */
#ifndef __SHIP_H_INCLUDED
#define __SHIP_H_INCLUDED

#include "shipClass.h"
#include "util.h"

class Ship
{
    cell origin;
    Direction direction;
    int hits;
    ShipClass shipClass;

public:
    Ship(cell o, ShipClass sc, Direction d);
    std::vector<cell> containedCells();
    ShipClass getShipClass();
};
#endif