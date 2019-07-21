/*
* board.h
* Represents a grid-shapes board that holds zero or more Ships
* Benjamin Lovy
*/
#ifndef __BOARD_H_INCLUDED
#define __BOARD_H_INCLUDED

#include <string>
#include <vector>

#include "ship.h"

class Board
{
    std::vector<Ship> ships;
    public:
        int size;
        Board();
        std::vector<std::string> toLineStrings();
};

#endif