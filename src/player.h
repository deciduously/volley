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
    cell getOrigin(ShipClass sc);
    ShipClass getShipClass();
    void placeShip(cell o, ShipClass sc, Direction d);

protected:
    Board board;
    std::vector<ShipClass> unassignedShips;

public:
    Player(int boardSize = BOARD_SIZE);
    lines toLineStrings();
    std::string toString();
    void runPlacement();
};
#endif