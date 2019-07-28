/*
* game.h
* Top-level Battleship game object
* Benjamin Lovy
*/
#ifndef __GAME_H_INCLUDED
#define __GAME_H_INCLUDED

#include "computer.h"

class Game
{
    Player *player;
    Computer *computer;
    GameState gameState;
    Cell getRandomTarget(Player &opponent);
    Cell promptTarget();
    void runFiring();
    void runPlacement();
    std::string toStringFiring();

public:
    Game(int boardSize = BOARD_SIZE);
    ~Game();
    void run();
    int size();
};
#endif