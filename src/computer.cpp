/*
* computer.cpp
* Inherits from Player, represents the automated computer opponent in Battleship
* Benjamin Lovy
 */
#include <algorithm>
#include <iostream>

#include "computer.h"

//
// PRIVATE METHODS
//

// Handle a hit
void Computer::registerHit(int shipsBefore, const Cell target, const Player &opponent)
{
    Board *opponentBoard = opponent.getBoardConst();
    if (!isSeeking)
    {
        // switch on seeking mode
        isSeeking = true;

        // populate neighborhood
        neighborhood = opponentBoard->getNeighborhood(target);
    }
    else
    {
        // first check if something sank.  We can skip everything else if so
        if (opponentBoard->remainingShipsCount() < shipsBefore)
        {
            isSeeking = false;
            return;
        }

        // if it did hit and it is seeking, update the neighborhood
        // Add the new cell to try
        // Drop cells in the wrong direction
        // Grab the most recent hit - it's one before the one we just fired
        Cell lastHit = hits[hits.size() - 2];
        // check which direction we hit from there
        if (lastHit.row == target.row)
        {
            // horizontal
            // prune neighborhood of any cells that aren't in this row
            neighborhood.erase(std::remove_if(neighborhood.begin(), neighborhood.end(), [target](const Cell &c) {
                                   return c.row != target.row;
                               }),
                               neighborhood.end());
            // add the next cell
            if (lastHit.col > target.col)
            {
                if (target.col > 1)
                    neighborhood.push_back(Cell(target.row, static_cast<char>(target.col - 1)));
            }
            else
            {
                if (target.col < opponentBoard->size())
                    neighborhood.push_back(Cell(target.row, static_cast<char>(target.col + 1)));
            }
        }
        else
        {
            // vertical
            // prune neighborhood of any cells that aren't in this column
            neighborhood.erase(std::remove_if(neighborhood.begin(), neighborhood.end(), [target](const Cell &c) {
                                   return c.col != target.col;
                               }),
                               neighborhood.end());
            // add the next cell
            if (lastHit.row > target.row)
            {
                if (target.row > 1)
                    neighborhood.push_back(Cell(target.row - 1, target.col));
            }
            else
            {
                if (target.row < opponentBoard->size())
                    neighborhood.push_back(Cell(target.row + 1, target.col));
            }
        }
    }
}

//
// PUBLIC METHODS
//

// SEEKING
// When a hit is found, toggle a boolean isSeeking and populate the neighborhood
// This vector will hold cells above, below, left, and right of the hit
// If seeking, instead of choosing random cells, pick from the neighborhood
// Once a ship comes back "Sunk", revert to random fire

// Choose a target on the given opponent and fire a shot at it
void Computer::executeFire(Player &opponent)
{
    Board *opponentBoard = opponent.getBoardConst();
    int shipsBefore = opponentBoard->remainingShipsCount();
    bool didHit = false;
    Cell chosenTarget = Cell();
    if (isSeeking)
    {
        // SEEK
        // Get the size of the neighborhood, pick a random idx to fire at
        // remove that cell from the neighboorhood
        // if the neighborhood is empty, something has gone wrong
        // there should always be one when seeking
        int numOptions = neighborhood.size();
        int randomIdx = 0; // init to zero - totally fine to use
        // choose a target that has not been fired at yet
        int runs = numOptions;
        do
        {
            // TODO it seems like sometimes the second-to-last shot of a ship ends up firing randomly
            // but then it still knows to come back for it??
            if (runs == 0)
            {
                // we tried them all, but all had already received fire.
                chosenTarget = opponentBoard->getRandomTarget();
                break;
            }
            randomIdx = rand() % numOptions; // random between 0 and size-1
            chosenTarget = neighborhood[randomIdx];
            runs--;
        } while (opponentBoard->hasReceived(chosenTarget));

        if (runs != 0)
        {
            // only clear the neighborhood if we actually found one
            neighborhood.erase(neighborhood.begin() + randomIdx);
        }
    }
    else
    {
        // Otherwise, just fire randomly
        chosenTarget = opponentBoard->getRandomTarget();
    }

    std::cout << "Computer fires at: " << chosenTarget << std::endl;
    didHit = fireShot(chosenTarget, opponent);

    // register the hit if needed
    if (didHit)
        registerHit(shipsBefore, chosenTarget, opponent);
}

// Automatically place all ships
void Computer::runPlacement()
{
    randomlyPlaceShips();
}

// Return the board as a vector of strings, one per line
lines Computer::toLineStrings(const GameState gs) const
{
    // add "Player"  - or "Computer" ? -  header
    lines ret = {};

    // 15 spaces in
    ret.push_back("               Computer");
    ret.push_back("Ships alive:");
    ret.push_back(remainingShipsStr(gs));
    ret.push_back("");
    // insert board line strings
    lines boardLines = board->toLineStrings(false);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}
