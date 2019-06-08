#ifndef __PLAYER_H_INCLUDED
#define __PLAYER_H_INCLUDED

#include <vector>

#include "board.h"

class Player
{
    Board board;
    std::vector<ShipClass> unassignedShips;
    public:
        Player();
        std::string toString();
};
#endif