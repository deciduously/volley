#include "ship.h"

// ShipPlacement default constructor
ShipPlacement::ShipPlacement()
{
}

// Should always use explicit constructor
ShipPlacement::ShipPlacement(Cell c, Direction d, ShipClass sc)
{
    cell = c;
    direction = d;
    shipClass = sc;
}

// Return a vector containing each cell this ship occupies
std::vector<Cell> ShipPlacement::containedCells() const
{
    //initalise return vector
    std::vector<Cell> ret = {cell};

    // Add the rest of the ship
    for (int i = 1; i < shipClass.size(); i++)
    {
        switch (direction)
        {
        case Direction::Left:
            // de-letter it
            ret.push_back(Cell(cell.row, cell.col + i - 64));
            break;
        case Direction::Down:
            ret.push_back(Cell(cell.row + i, cell.col));
            break;
        }
    }

    // return it
    return ret;
}

//
// PUBLIC METHODS
//

// Ship constructor
Ship::Ship(ShipPlacement sp)
{
    // set members
    placement = sp;
    hits = placement.shipClass.size();
}

// Getter for contained cells, for convenience
std::vector<Cell> Ship::containedCells() const
{
    return placement.containedCells();
}

// Getter for ShipClass
ShipClass Ship::getShipClass() const
{
    return placement.shipClass;
}