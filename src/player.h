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
    Cell getOrigin(ShipClass sc);
    Direction getRandomDirection(Cell origin, ShipClass sc);
    Cell getRandomOrigin(ShipClass sc);
    ShipClass getShipClass();
    std::vector<Cell> hits;
    std::vector<Cell> misses;
    void placeShip(ShipPlacement sp);

protected:
    Board board;
    std::vector<ShipClass> unassignedShips;
    void randomlyPlaceShips();

public:
    Player(int boardSize = BOARD_SIZE);
    void fireShot(Cell target, Player &opponent);
    std::vector<Cell> getAllShots();
    Board getBoard();
    lines toLineStrings();
    std::string toString();
    void runPlacement();
};
#endif