/*
* game.h
* Top-level Battleship game object
* Benjamin Lovy
*/
#ifndef __GAME_H_INCLUDED
#define __GAME_H_INCLUDED

#include "computer.h"
#include "player.h"

class Game
{
    Player player;
    Computer computer;
    public:
        Game();
        std::string toString();
};
#endif