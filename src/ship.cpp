#include "ship.h"

//
// PUBLIC METHODS
//

// Ship constructor
Ship::Ship(Cell o, ShipClass sc, Direction d)
{
    // set members
    origin = o;
    direction = d;
    shipClass = sc;
    hits = shipClass.size();
}

// Return a vector containing each cell this ship occupies
std::vector<Cell> Ship::containedCells()
{
    //initalise return vector
    std::vector<Cell> ret = {origin};

    // Add the rest of the ship
    for (int i = 1; i < shipClass.size(); i++)
    {
        switch (direction)
        {
        case Direction::Left:
            // de-letter it
            ret.push_back(Cell(origin.row, origin.col + i - 64));
            break;
        case Direction::Down:
            ret.push_back(Cell(origin.row + i, origin.col));
            break;
        }
    }

    // return it
    return ret;
}

// Getter for ShipClass
ShipClass Ship::getShipClass()
{
    return shipClass;
}