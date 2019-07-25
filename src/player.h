/*
* player.h
* Represents a player of a game of Battleship
* Contains their respective Board
* Benjamin Lovy
*/
#ifndef __PLAYER_H_INCLUDED
#define __PLAYER_H_INCLUDED

#include "board.h"

typedef std::tuple<origin, ShipClass, Direction> shipPlacement;

class Player
{
    Board board;
    origin getOrigin(ShipClass sc);
    ShipClass getShipClass();
    bool doesFit(shipPlacement osd);
    void placeShip(shipPlacement osd);
    std::vector<ShipClass> unassignedShips;

public:
    Player(int boardSize = BOARD_SIZE);
    lines toLineStrings();
    std::string toString();
    void runPlacement();
};
#endif