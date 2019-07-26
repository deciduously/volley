#include "ship.h"

// Ship constructor
Ship::Ship(cell o, ShipClass sc, Direction d)
{
    // set members
    origin = o;
    direction = d;
    shipClass = sc;
    hits = shipClass.size();
}

// Return a vector containing each cell this ship occupies
std::vector<cell> Ship::containedCells()
{
    //unpack origin
    int row;
    char col;
    std::tie(row, col) = origin;

    //initalise return vector
    std::vector<cell> ret = {origin};

    // Add the rest of the ship
    // TODO We don't check if it's legal at all - assuming runPlacement() did its job
    // Add some checks
    for (int i = 1; i < shipClass.size() - 1; i++)
    {
        switch (direction)
        {
        case Direction::Left:
            ret.push_back({row, col + i});
            break;
        case Direction::Down:
            ret.push_back({row + i, col});
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