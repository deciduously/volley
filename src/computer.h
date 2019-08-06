/*
* computer.h
* Inherits from Player, represents the automated computer opponent in Battleship
* Benjamin Lovy
 */
#ifndef __COMPUTER_H_INCLUDED
#define __COMPUTER_H_INCLUDED

#include "player.h"

// SEEKING
// When a hit is found, toggle a boolean isSeeking and populate the neighborhood
// This vector will hold cells above, below, left, and right of the hit
// If seeking, instead of choosing random cells, pick from the neighborhood
// DECIDE - when we find the next hit, should we drop the cells going the wrong way?
// Once a ship comes back "Sunk", revert to random fire

class Computer : public Player
{
    // When seeking, the un-hit cells around cells we have hit to pull from
    std::vector<Cell> neighborhood;
    // Store whether or not we are actively seeking for a ship
    bool isSeeking;

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