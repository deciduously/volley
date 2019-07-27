/*
* board.h
* Represents a grid-shapes board that holds zero or more Ships
* Benjamin Lovy
*/
#ifndef __BOARD_H_INCLUDED
#define __BOARD_H_INCLUDED

#include "ship.h"

class Board
{
    int size;
    std::vector<Ship> ships;

public:
    Board(int boardSize = BOARD_SIZE);
    bool doesFit(cell o, ShipClassType sct, Direction d);
    char getCharAt(cell c, bool showShips);
    void pushShip(Ship s);
    lines toLineStrings(bool showShips);
};

#endif