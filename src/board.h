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
    bool doesFit(ShipPlacement sp) const;
    char getCharAt(Cell c, bool showShips) const;
    Cell getRandomCell() const;
    Cell getRandomTarget() const;
    Cell promptCell(const std::string &promptStr) const;
    void pushShip(Ship s);
    bool receiveShot(Cell target);
    int remainingShipsCount() const;
    std::vector<ShipClass> remainingShips() const;
    void removeShip(ShipClass sc);
    int size() const;
    lines toLineStrings(bool showShips) const;
};

#endif