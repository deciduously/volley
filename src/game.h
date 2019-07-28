/*
* game.h
* Top-level Battleship game object
* Benjamin Lovy
*/
#ifndef __GAME_H_INCLUDED
#define __GAME_H_INCLUDED

// NOTE I tried forward-declarding:

// class Computer;
// Class Player;

// but it broke everyinthing with "incomplete type" errors

#include "computer.h"

class Game
{
    Player *player;
    Computer *computer;
    GameState gameState;
    Cell getRandomTarget(const Player &opponent) const;
    Cell promptTarget() const;
    void runFiring();
    void runPlacement();
    std::string toStringFiring() const;

public:
    Game(int boardSize = BOARD_SIZE);
    ~Game();
    void run();
    int size() const;
};
#endif