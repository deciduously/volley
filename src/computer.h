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
    // When seeking, the un-hit cells around cells we have hit to pull from
    std::vector<Cell> neighborhood;

public:
    // Inherits Player constructor with different default name
    Computer(std::string name = "The Computer", int boardSize = BOARD_SIZE) : Player(name, boardSize){};
    // Automatically place all ships
    void runPlacement();
    // Return the board as a vector of strings, one per line
    lines toLineStrings(const GameState gs = GameState::Firing) const;
};

#endif