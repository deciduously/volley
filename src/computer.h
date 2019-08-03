/*
* computer.h
* Inherits from Player, represents the automated computer opponent in Battleship
* Benjamin Lovy
 */
#ifndef __COMPUTER_H_INCLUDED
#define __COMPUTER_H_INCLUDED

#include "player.h"

// You need a seeking state


class Computer : public Player
{
    std::vector<Cell> neighborhood;

public:
    Computer(std::string name = "The Computer", int boardSize = BOARD_SIZE) : Player(name, boardSize){};
    void runPlacement();
    lines toLineStrings(const GameState gs = GameState::Firing) const;
};

#endif