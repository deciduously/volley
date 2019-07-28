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
    int dimension;
    std::vector<Cell> receivedShots;
    std::vector<Ship> ships;

public:
    Board(int boardSize = BOARD_SIZE);
    bool doesFit(ShipPlacement sp);
    char getCharAt(Cell c, bool showShips);
    Cell getRandomCell();
    Cell promptCell(std::string promptStr);
    void pushShip(Ship s);
    std::vector<Cell> getAllShots();
    bool receiveFire(Cell target);
    int size();
    lines toLineStrings(bool showShips);
};

#endif