/*
* board.h
* Represents a grid-shapes board that holds zero or more Ships
* Benjamin Lovy
*/
#ifndef __BOARD_H_INCLUDED
#define __BOARD_H_INCLUDED

#include "ship.h"

class Board
{
    // Board is a square, this many on a side
    int dimension;
    // Cells that have been fired at
    std::vector<Cell> receivedShots;
    // The ships this board stores
    std::vector<Ship> ships;

public:
    // Board constructor
    Board(int boardSize = BOARD_SIZE);
    // Check if a shipPlacement would fit on the board before creating a Ship
    bool doesFit(const ShipPlacement sp) const;
    // Returns the corresponding cell character
    // Pass true to show ship locations, false to only show hits/misses
    char getCharAt(const Cell c, bool showShips) const;
    // Return the cells above, below, left, and right of the given cell
    // Performs bounds checking - if a neighbor is off the board, it is not returned
    std::vector<Cell> getNeighborhood(const Cell c) const;
    // Get a random cell on the board
    Cell getRandomCell() const;
    // Get a random cell on the board that doesn't appear in receivedShots
    Cell getRandomTarget() const;
    // Return whether or not a given cell has already received fire
    bool hasReceived(const Cell c) const;
    // Method to prompt the user for a cell, ensuring its a valid spot on this board
    // Returning a default cell indicates 'R', or random
    Cell promptCell(const std::string &promptStr) const;
    // Add a ship to the board
    void pushShip(const Ship s);
    // Receive a shot at a cell, return true if it's a hit
    ShipClass receiveShot(const Cell target);
    // get how many ships still have health
    int remainingShipsCount() const;
    // Return all the remaining alive ship classes
    std::vector<ShipClass> remainingShips() const;
    // Remove the ship with the given ship class if found, otherwise do nothing
    // Used to build a preview
    void removeAllShips();
    // Used to build a "preview" board during placement - could also use if a ship hits zero i guess? no need really
    void removeShip(const ShipClass sc);
    // Getter for board dimension
    int size() const;
    // Returns a vector of strings, one for each line of this board
    // pass true to show ship locations, false to only show hits/misses
    lines toLineStrings(bool showShips) const;
};

#endif