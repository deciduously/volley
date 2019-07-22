/*
* player.h
* Represents a player of a game of Battleship
* Contains their respective Board
* Benjamin Lovy
*/
#ifndef __PLAYER_H_INCLUDED
#define __PLAYER_H_INCLUDED

#include "board.h"

class Player
{
    Board board;
    std::vector<ShipClass> unassignedShips;
    std::string unassignedShipLetters();
    public:
        Player();
        lines toLineStrings();
        std::string toString();
        void runPlacement();
};
#endif