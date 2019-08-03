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
    int dimension;
    std::vector<Cell> receivedShots;
    std::vector<Ship> ships;

public:
    // Board constructor
    Board(int boardSize = BOARD_SIZE);
    // Check if a shipPlacement would fit on the board before creating a Ship
    bool doesFit(ShipPlacement sp) const;
    // Returns the corresponding cell character
    // Pass true to show ship locations, false to only show hits/misses
    char getCharAt(Cell c, bool showShips) const;
    // Get a random cell on the board
    Cell getRandomCell() const;
    // Get a random cell on the board that doesn't appear in receivedShots
    Cell getRandomTarget() const;
    // Method to prompt the user for a cell, ensuring its a valid spot on this board
    // Returning a default cell indicates 'R', or random
    Cell promptCell(const std::string &promptStr) const;
    // Add a ship to the board
    void pushShip(Ship s);
    // Receive a shot at a cell, return true if it's a hit
    ShipClass receiveShot(Cell target);
    // get how many ships still have health
    int remainingShipsCount() const;
    // Return all the remaining alive ship classes
    std::vector<ShipClass> remainingShips() const;
    // Remove the ship with the given ship class if found, otherwise do nothing
    // Used to build a "preview" board during placement - could also use if a ship hits zero i guess? no need really
    void removeShip(ShipClass sc);
    // Getter for board dimension
    int size() const;
    // Returns a vector of strings, one for each line of this board
    // pass true to show ship locations, false to only show hits/misses
    lines toLineStrings(bool showShips) const;
};

#endif