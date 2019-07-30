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
    Cell getOrigin(ShipClass sc) const;
    Direction getRandomDirection(Cell origin, ShipClass sc) const;
    Cell getRandomOrigin(ShipClass sc) const;
    ShipClass getShipClass() const;
    std::vector<Cell> hits;
    std::vector<Cell> misses;
    void placeShip(ShipPlacement sp);

protected:
    Board board;
    std::vector<ShipClass> unassignedShips;
    void randomlyPlaceShips();
    int remainingShips() const;

public:
    Player(int boardSize = BOARD_SIZE);
    void fireShot(Cell target, Player &opponent);
    std::vector<Cell> getAllShots() const;
    Board getBoard();
    Board getBoardConst() const;
    lines toLineStrings() const;
    bool receiveShot(Cell target);
    void runPlacement();
};

#endif