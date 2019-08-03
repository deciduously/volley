/*
* player.h
* Represents a player of a game of Battleship
* Contains their respective Board
* Benjamin Lovy
*/
#ifndef __PLAYER_H_INCLUDED
#define __PLAYER_H_INCLUDED

#include "board.h"

class Player
{
    // Helper method to prompt user for origin
    Cell getOrigin(ShipClass sc) const;
    // Return a random direction for the given origin and shipclass that fit - it's already ensured at least one of the two does
    Direction getRandomDirection(Cell origin, ShipClass sc) const;
    // Returns a random origin for a given ShipClass guaranteed to work in at least one direction
    Cell getRandomOrigin(ShipClass sc) const;
    // Helper method to prompt user a single ship input
    ShipClass getShipClass() const;
    std::vector<Cell> hits;
    std::vector<Cell> misses;
    std::string name;
    // Places a ship
    void placeShip(ShipPlacement sp);

protected:
    Board *board;
    std::vector<ShipClass> unassignedShips;
    // Randomly choose placements for all remaining unassigned ships
    // Computer always uses this, player is given the option at each ship placement to do for the rest
    void randomlyPlaceShips();
    // Helper function to pretty-print the vector of shipclasses
    std::string remainingShipsStr(const GameState gs) const;

public:
    // Constructor
    Player(std::string name = "The Player", int boardSize = BOARD_SIZE);
    // Destructor
    ~Player();
    // Record the result of a shit
    // True indicates a hit, false a miss
    void fireShot(Cell target, Player &opponent);
    // Getter for the board -- TODO should the caller just use const_cast?
    Board *getBoard();
    // Const Getter for the board
    Board *getBoardConst() const;
    // Getter for name
    std::string getName() const;
    // Receive a shot
    ShipClass receiveShot(Cell target);
    // Returns the number of ships with a positive number of hits
    int remainingShipsCount() const;
    // Run the placement loop to prompt user for ship locations
    void runPlacement();
    // Return the board output as a vector of strings, one per line
    lines toLineStrings(const GameState gs = GameState::Firing) const;
};
#endif