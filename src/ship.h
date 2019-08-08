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
    // The origin cell
    Cell cell;
    // The direction from the origin: Right | Down
    Direction direction = Direction::Right;
    // The class of ship
    ShipClass shipClass = ShipClass();
    // ShipPlacement default constructor
    ShipPlacement();
    // Should always use explicit constructor
    ShipPlacement(const Cell c, const Direction d, const ShipClass sc);
    // Return a vector containing each cell this ship occupies
    std::vector<Cell> containedCells() const;
} ShipPlacement;

// A placement that keeps track of health
class Ship
{
    // This ship's position
    ShipPlacement placement;
    // The number of hits this ship can take
    int hits;

public:
    // Ship constructor
    Ship(const ShipPlacement sp);
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