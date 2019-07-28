#include "computer.h"

// Automatically place all ships
void Computer::runPlacement()
{
    randomlyPlaceShips();
}

lines Computer::toLineStrings() const
{
    // add "Player"  - or "Computer" ? -  header
    lines ret = {};

    // 15 spaces in
    std::string headerLine = "               Computer";

    ret.push_back(headerLine);
    ret.push_back("");
    // insert board line strings
    lines boardLines = board.toLineStrings(true);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}
