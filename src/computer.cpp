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
    ret.push_back("               Computer");
    std::string shipsRemainLine = "                 Ships alive: ";
    shipsRemainLine.append(std::to_string(remainingShips()));
    ret.push_back(shipsRemainLine);
    ret.push_back("");
    // insert board line strings
    lines boardLines = board.toLineStrings(false);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}
