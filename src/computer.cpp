#include "computer.h"

// will keep track of total hits found and compare if it sank any
//if there's a mismatch, keep seeking until you hit again, then drop the neighborhood and start  hitting that direction

// Automatically place all ships
void Computer::runPlacement()
{
    randomlyPlaceShips();
}

// Return the board as a vector of strings, one per line
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
    lines boardLines = board->toLineStrings(false);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}
