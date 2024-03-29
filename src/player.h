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
    // Display name of this player
    std::string name;
    // Places a ship
    void placeShip(ShipPlacement sp);

protected:
    // Pointer to the board
    Board *board;
    // Stored successful shots this player has made
    std::vector<Cell> hits;
    // Any ships allocated to the player that have not been placed on the board
    std::vector<ShipClass> unassignedShips;
    // Randomly choose placements for all remaining unassigned ships
    // Computer always uses this, player is given the option at each ship placement to do for the rest
    void randomlyPlaceShips();
    // Helper function to pretty-print the vector of shipclasses
    std::string remainingShipsStr(const GameState gs) const;

public:
    //Default Constructor
    Player();
    // Constructor
    Player(int boardSize, std::string n = "The Player");
    // Destructor
    ~Player();
    // Record the result of a shit
    // True indicates a hit, false a miss
    bool fireShot(Cell target, Player &opponent);
    // Getter for the board
    Board *getBoard();
    // Const getter for the board
    Board *getBoardConst() const;
    // Getter for name
    std::string getName() const;
    // Receive a shot
    ShipClass receiveShot(const Cell target);
    // Returns the number of ships with a positive number of hits
    int remainingShipsCount() const;
    // Run the placement loop to prompt user for ship locations
    void runPlacement();
    // Return the board output as a vector of strings, one per line
    lines toLineStrings(const GameState gs = GameState::Firing) const;
};
#endif