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
    std::string name;
    void placeShip(ShipPlacement sp);

protected:
    Board *board;
    std::vector<ShipClass> unassignedShips;
    void randomlyPlaceShips();
    std::string remainingShipsStr(const GameState gs) const;

public:
    Player(std::string name = "The Player", int boardSize = BOARD_SIZE);
    ~Player();
    void fireShot(Cell target, Player &opponent);
    Board *getBoard();
    Board *getBoardConst() const;
    std::string getName() const;
    lines toLineStrings(const GameState gs = GameState::Firing) const;
    ShipClass receiveShot(Cell target);
    int remainingShipsCount() const;
    void runPlacement();
};

// stream override
std::ostream &operator<<(std::ostream &stream, const Player &p);
#endif