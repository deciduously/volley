#ifndef __BOARD_H_INCLUDED
#define __BOARD_H_INCLUDED

#include <string>
#include <vector>

#include "ship.h"

class Board
{
    int size;
    std::vector<Ship> ships;
    public:
        Board();
        std::string toString();

};

#endif