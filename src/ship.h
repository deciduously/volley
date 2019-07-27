/*
* ship.h
* Represents a single ship on the battleship game board
* Benjamin Lovy
 */
#ifndef __SHIP_H_INCLUDED
#define __SHIP_H_INCLUDED

#include "util.h"

// An absolute ship location on the board
typedef struct ShipPlacement
{
    Cell cell;
    Direction direction;
    ShipClass shipClass;
    ShipPlacement();
    ShipPlacement(Cell c, Direction d, ShipClass sc);
    std::vector<Cell> containedCells();
} ShipPlacement;

class Ship
{
    ShipPlacement placement;
    int hits;

public:
    Ship(ShipPlacement sp);
    std::vector<Cell> containedCells();
    ShipClass getShipClass();
};
#endif