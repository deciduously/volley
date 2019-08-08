/*
* computer.cpp
* Inherits from Player, represents the automated computer opponent in Battleship
* Benjamin Lovy
 */
#include <algorithm>
#include <iostream>

#include "computer.h"

// will keep track of total hits found and compare if it sank any
//if there's a mismatch, keep seeking until you hit again, then drop the neighborhood and start  hitting that direction

// Return the cells above, below, left, and right of the given cell
// Performs bounds checking - if a neighbor is off the board, it is not returned
std::vector<Cell> getNeighborhood(Cell c, int boardSize)
{
    std::vector<Cell> ret = {};
    // up
    if (c.row > 1)
        ret.push_back(Cell(c.row - 1, c.col));
    // down
    if (c.row < boardSize)
        ret.push_back(Cell(c.row + 1, c.col));
    // left
    if (c.col > 'A')
        ret.push_back(Cell(c.row, static_cast<char>(c.col - 1)));
    // right
    if (c.col < boardSize + 64)
        ret.push_back(Cell(c.row, static_cast<char>(c.col + 1)));
    return ret;
}

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

    // if not seeking and it was a hit, enable seeking
    if (didHit)
    {
        if (!isSeeking)
        {
            // switch on seeking mode
            isSeeking = true;

            // populate neighborhood
            neighborhood = getNeighborhood(chosenTarget, board->size());
        }
        else
        {
            // first check if something sank.  We can skip everything else if so
            if (opponent.getBoardConst()->remainingShipsCount() < shipsBefore)
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
            if (lastHit.row == chosenTarget.row)
            {
                // horizontal
                // prune neighborhood of any cells that aren't in this row
                neighborhood.erase(std::remove_if(neighborhood.begin(), neighborhood.end(), [chosenTarget](const Cell &c) {
                                       return c.row != chosenTarget.row;
                                   }),
                                   neighborhood.end());
                // add the next cell
                if (lastHit.col > chosenTarget.col)
                {
                    if (chosenTarget.col > 1)
                        neighborhood.push_back(Cell(chosenTarget.row, static_cast<char>(chosenTarget.col - 1)));
                }
                else
                {
                    if (chosenTarget.col < opponentBoard->size())
                        neighborhood.push_back(Cell(chosenTarget.row, static_cast<char>(chosenTarget.col + 1)));
                }
            }
            else
            {
                // vertical
                // prune neighborhood of any cells that aren't in this column
                neighborhood.erase(std::remove_if(neighborhood.begin(), neighborhood.end(), [chosenTarget](const Cell &c) {
                                       return c.col != chosenTarget.col;
                                   }),
                                   neighborhood.end());
                // add the next cell
                if (lastHit.row > chosenTarget.row)
                {
                    if (chosenTarget.row > 1)
                        neighborhood.push_back(Cell(chosenTarget.row - 1, chosenTarget.col));
                }
                else
                {
                    if (chosenTarget.row < opponentBoard->size())
                        neighborhood.push_back(Cell(chosenTarget.row + 1, chosenTarget.col));
                }
            }
        }
    }
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
