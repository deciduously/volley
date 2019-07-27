#include "computer.h"

// Automatically place all ships - currently just goes in order
void Computer::runPlacement()
{
    // iterate through ships.size()
    //int shipsSize = unassignedShips.size();

    /*{ // choose a random origin
            // choose a random direction    }
            // after each, erase() it
            //
            */
}

lines Computer::toLineStrings()
{
    // add "Player"  - or "Computer" ? -  header
    lines ret = {};

    // 15 spaces in
    std::string headerLine = "               Computer\n";

    ret.push_back(headerLine);
    // insert board line strings
    lines boardLines = board.toLineStrings();
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}
