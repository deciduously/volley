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
    Direction direction = Direction::Right;
    ShipClass shipClass = ShipClass();
    // ShipPlacement default constructor
    ShipPlacement();
    // Should always use explicit constructor
    ShipPlacement(Cell c, Direction d, ShipClass sc);
    // Return a vector containing each cell this ship occupies
    std::vector<Cell> containedCells() const;
} ShipPlacement;

class Ship
{
    ShipPlacement placement;
    int hits;

public:
    // Ship constructor
    Ship(ShipPlacement sp);
    // Getter for ShipPlacement::ContainedCells(), for convenience
    std::vector<Cell> containedCells() const;
    // Getter for Hits
    int getHits() const;
    // Take a hit
    void takeHit();
    // Getter for ShipClass
    ShipClass getShipClass() const;
};
#endif