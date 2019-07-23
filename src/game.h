/*
* game.h
* Top-level Battleship game object
* Benjamin Lovy
*/
#ifndef __GAME_H_INCLUDED
#define __GAME_H_INCLUDED

#include "computer.h"

const int BOARD_SIZE = 10;

class Game
{
    int size = BOARD_SIZE;
    Player player;
    Computer computer;
    GameState gameState;
    std::string toStringFiring();
    void runFiring();
    void runPlacement();
    public:
        Game();
        void run();
        int getSize();
};
#endif