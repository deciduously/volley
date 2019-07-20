/*
* computer.h
* Inherits from Player, represents the automated computer opponent in Battleship
* Benjamin Lovy
 */
#ifndef __COMPUTER_H_INCLUDED
#define __COMPUTER_H_INCLUDED

#include <tuple>

#include "player.h"

class Computer : public Player
{
    std::vector<std::tuple<int, int>> neighborhood;
    public:
        Computer();
};

#endif