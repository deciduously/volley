#include "ship.h"

// Ship constructor
Ship::Ship(int row, char col, Direction dir, ShipClass sc)
{
    origin = std::make_tuple(row, col);
    direction = dir;
    shipClass = sc;
    hits = shipClass.size();
}
