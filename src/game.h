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
    // Pointer to the Player object
    Player *player;
    // Pointer to the Computer object
    Computer *computer;
    // One of Placement | Firing | GameOver
    GameState gameState;
    // Return a vector of strings containing both boards side by side
    lines bothBoardLines() const;
    // Pick a random target avoiding a specific board's recorded hits and misses
    Cell getRandomTarget(const Player &opponent) const;
    // Prompt the user for a target
    Cell promptTarget() const;
    // Reset a completed game to play again
    void resetGame();
    // Run the fire loop until someone wins
    bool runFiring();
    // Run ship placement for both players
    void runPlacement();

public:
    // Constructor
    Game(int boardSize = BOARD_SIZE);
    // Destructor
    ~Game();
    // Run the game
    void run();
    // Getter for board size
    int size() const;
};

#endif