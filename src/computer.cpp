#include "computer.h"

// Automatically place all ships
void Computer::runPlacement()
{
    randomlyPlaceShips();
}

lines Computer::toLineStrings(const GameState gs) const
{
    // add "Player"  - or "Computer" ? -  header
    lines ret = {};

    // 15 spaces in
    ret.push_back("               Computer");
    ret.push_back("Ships alive:");
    ret.push_back(remainingShipsStr(gs));
    ret.push_back("");
    // insert board line strings
    lines boardLines = board.toLineStrings(false);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}
