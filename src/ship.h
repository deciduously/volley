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
    Ship(int row, char col, Direction dir, ShipClass sc);
};
#endif