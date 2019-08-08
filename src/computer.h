/*
* computer.h
* Inherits from Player, represents the automated computer opponent in Battleship
* Benjamin Lovy
 */
#ifndef __COMPUTER_H_INCLUDED
#define __COMPUTER_H_INCLUDED

#include "player.h"

class Computer : public Player
{
    // When seeking, the un-hit cells around cells we have hit to pull from
    std::vector<Cell> neighborhood;
    // Store whether or not we are actively seeking for a ship
    bool isSeeking;
    // Handle a hit
    void registerHit(int shipsBefore, const Cell target, const Player &opponent);

public:
    // Inherits Player constructor with different default name
    Computer(int boardSize = BOARD_SIZE) : Player(boardSize, "The Computer")
    {
        isSeeking = false;
    };
    // Choose a target on the given opponent and fire a shot at it
    void executeFire(Player &opponent);
    // Automatically place all ships
    void runPlacement();
    // Return the board as a vector of strings, one per line
    lines toLineStrings(const GameState gs = GameState::Firing) const;
};

#endif