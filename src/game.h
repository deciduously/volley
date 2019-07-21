/*
* game.h
* Top-level Battleship game object
* Benjamin Lovy
*/
#ifndef __GAME_H_INCLUDED
#define __GAME_H_INCLUDED

#include "computer.h"
#include "player.h"
#include "util.h"

class Game
{
    Player player;
    Computer computer;
    GameState gameState;
    std::string toStringFiring();
    void runFiring();
    void runPlacement();
    public:
        Game();
        void run();
};
#endif