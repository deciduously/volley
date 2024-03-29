/*
* board.cpp
* Represents a grid-shapes board that holds zero or more Ships
* Benjamin Lovy
*/
#include <algorithm>
#include <iostream>
#include <regex>

#include "board.h"

// Helper function to add a cell to a string with padding from a char
inline void pushCharCell(std::string &s, char contents)
{
    s.push_back(' ');
    s.push_back(contents);
    s.push_back(' ');
}

// Board constructor
Board::Board(int boardSize)
{
    dimension = boardSize; // All boards are 10, hardcoded in "game.h" (A-J)
}

// Check if a shipPlacement would fit on the board before creating a Ship
bool Board::doesFit(const ShipPlacement sp) const
{
    // check each cell the ship would occupy
    // build the hypthetical ship and store its contained cells
    std::vector<Cell> cells = sp.containedCells();
    for (auto &c : cells)
    {
        if (getCharAt(c, true) != '.')
        {
            return false;
        }
    }
    return true;
}

// Returns the corresponding cell character
// Pass true to show ship locations, false to only show hits/misses
char Board::getCharAt(const Cell &c, bool showShips) const
{
    using std::find;
    using std::vector;

    // if row or col out of bounds, return 'E'
    if (c.row < 1 || c.row > dimension || c.col < 'A' || c.col >= ('A' + dimension))
    {
        return 'E';
    }

    // init return value to default (empty)
    char ret = '.';

    // Add the ships

    // loop through ships
    for (auto &s : ships)
    {
        // each ship, loop through the contained cells
        vector<Cell> cells = s.containedCells();

        // if any of them are found in cells, set ret to that ship character
        // runPlacement should have avoided any overlaps
        if (find(cells.begin(), cells.end(), c) != cells.end())
        {
            ret = s.getShipClass().toChar();
        }
    }

    // Overlay hits and misses
    if (hasReceived(c))
    {
        if (ret == '.')
        {
            ret = 'O';
        }
        else
        {
            ret = 'X';
        }
    }

    if (!showShips)
    {
        // if its a ship and not an x or an o, turn it back to .
        if (ret != 'X' && ret != 'O')
        {
            if (ret != '.')
                ret = '.';
        }
    }

    return ret;
}

// Return the cells above, below, left, and right of the given cell
// Performs bounds checking - if a neighbor is off the board, it is not returned
std::vector<Cell> Board::getNeighborhood(const Cell &c) const
{
    std::vector<Cell> ret = {};
    // up
    if (c.row > 1)
        ret.push_back(Cell(c.row - 1, c.col));
    // down
    if (c.row < dimension)
        ret.push_back(Cell(c.row + 1, c.col));
    // left
    if (c.col > 'A')
        ret.push_back(Cell(c.row, static_cast<char>(c.col - 1)));
    // right
    if (c.col < dimension + 64)
        ret.push_back(Cell(c.row, static_cast<char>(c.col + 1)));
    return ret;
}

// Get a random cell on the board
Cell Board::getRandomCell() const
{
    // get two random numbers between 1 and board size
    int max = size();
    int row = rand() % max + 1;
    int colNum = rand() % max + 1;

    // return as a cell
    return Cell(row, colNum);
}

// Get a random cell on the board that doesn't appear in receivedShots
Cell Board::getRandomTarget() const
{
    Cell ret = Cell();
    do
    {
        ret = getRandomCell();
    } while (hasReceived(ret));
    return ret;
}

// Return whether or not a given cell has already received fire
bool Board::hasReceived(const Cell &c) const
{
    return (std::find(receivedShots.begin(), receivedShots.end(), c) != receivedShots.end());
}

// Method to prompt the user for a cell, ensuring its a valid spot on this board
// Returning a default cell indicates 'R', or random
Cell Board::promptCell(const std::string &promptStr) const
{
    using std::cerr;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::regex;
    using std::string;

    // loop forever - will break if successful
    for (;;)
    {
        //prompt for input
        string originStr;
        cout << "Enter " << promptStr << ".  'R' for random.  (e.g. \"A1\" | \"a1\" | \"1A\" | \"1a\")> ";
        cin >> originStr;

        // catch random
        if (originStr.size() == 1 && toupper(originStr[0]) == 'R')
        {
            cout << "Rolling the dice..." << endl;
            return getRandomTarget();
        }

        // try to get a Cell from the input
        // if we fail - it's not an int and a char in either order (for now the right order) - loop again
        int row = 0;
        char col = 'Z';

        // Define pattern to match
        // NOTE - board size is hardcoded here.  If you parameterize, this will have to change
        static regex cellRe("^([0-9])([a-jA-J])$|^(10)([a-jA-J])$|^([a-jA-J])(10)$|^([a-jA-J])([0-9])$");

        // Use the flag to match on strings
        std::smatch m;

        // extract the input if possible
        if (std::regex_match(originStr, m, cellRe))
        {
            // on a successful match, fill in row and col
            // Skip first go, its the full match
            for (auto &match : m)
            {
                std::string sm = match.str();
                if (sm.size() == 0)
                    // skip empty matches that happen
                    continue;
                else if (sm.size() == 1)
                {
                    // most will be one in length, store to proper value
                    if (isalpha(sm[0]))
                        col = toupper(sm[0]);
                    else
                    {
                        row = stoi(sm);
                    }
                }
                else
                {
                    // if the match length is two, we know its a 10, store it as the row
                    row = 10;
                }
            }
        }
        else
        {
            // Regex failed to match
            cerr << "Please enter a cell on the board, either RowCol or ColRow." << endl
                 << "Valid rows are 1 through 10, valid columns are A through J." << endl;
            clearCin();
            continue;
        }
        Cell ret = Cell(row, col);
        // if it fits, check if it's taken
        // only run this if we're prompting for a target
        if (promptStr == "Target")
        {
            if (hasReceived(ret))
            {
                cout << "That's taken!" << endl;
                clearCin();
                continue;
            }
        }
        // If we made it through all checks, it's a valid choice.  Return it.
        return Cell(row, col);
    }
}

// Add a ship to the board
void Board::pushShip(const Ship s)
{
    ships.push_back(s);
}

// Receive a shot at a cell, return true if it's a hit
ShipClass Board::receiveShot(const Cell target)
{
    char result = getCharAt(target, true);
    receivedShots.push_back(target);
    bool ret = result != '.';
    // record hit if true
    if (ret)
    {
        for (auto &s : ships)
        {
            if (result == s.getShipClass().toChar())
            {
                s.takeHit();
            }
        }
    }
    // TODO this is a little roundabout - a direct char->shipClassType is probably better?
    return ShipClass(result);
}

// get how many ships still have health
int Board::remainingShipsCount() const
{
    // Before we've started, there are no ships
    // This means we're in Placement, return the total number of ships
    if (ships.size() == 0)
        return ALL_SHIP_CLASSES.size();

    int ret = 0;
    for (auto &s : ships)
    {
        if (s.getHits() > 0)
        {
            ret++;
        }
    }
    return ret;
}

// Return all the remaining alive ship classes
std::vector<ShipClass> Board::remainingShips() const
{
    // Before we've started, there are no ships
    // This means we're in Placement, return the total number of ships
    // I don't intend to ever call this but here it is
    if (ships.size() == 0)
        return ALL_SHIP_CLASSES;

    std::vector<ShipClass> ret = {};
    for (auto &s : ships)
    {
        if (s.getHits() > 0)
        {
            ret.push_back(s.getShipClass());
        }
    }
    return ret;
}

// Remove the ship with the given ship class if found, otherwise do nothing
// Used to build a preview
void Board::removeAllShips()
{
    while (ships.size() > 0)
    {
        removeShip(ships[0].getShipClass());
    }
}

// Remove the ship with the given ship class if found, otherwise do nothing
// Used to build a "preview" board during placement - could also use if a ship hits zero i guess? no need really
void Board::removeShip(const ShipClass sc)
{
    for (size_t i = 0; i < ships.size(); i++)
    {
        if (ships[i].getShipClass() == sc)
        {
            ships.erase(ships.begin() + i);
        }
    }
}

// Getter for board dimension
int Board::size() const
{
    return dimension;
}

// Returns a vector of strings, one for each line of this board
// pass true to show ship locations, false to only show hits/misses
lines Board::toLineStrings(bool showShips) const
{
    using std::string;
    using std::to_string;

    // Return vector
    lines ret = {};

    // Write the header column labels
    string headerLine = "";
    for (int i = 0; i <= dimension; i++)
    {
        // first one should be blank
        if (i == 0)
            pushCharCell(headerLine, ' ');
        else
            pushCharCell(headerLine, i + 64); // get the proper ASCII char
    }
    ret.push_back(headerLine);

    // add a blank lines
    ret.push_back("");

    // then, write the grid
    for (int row = 1; row <= dimension; row++)
    {
        string rowString = "";
        for (int col = 0; col <= dimension; col++)
        {
            if (col == 0)
            {
                // the first column of each row is the row number
                string strOfInt = to_string(row);
                int strLen = strOfInt.size();
                if (strLen == 1)
                {
                    // single-digit numbers can just use pushCharCell
                    pushCharCell(rowString, strOfInt[0]);
                }
                else if (strLen == 2)
                {
                    // by default this branch handles the 10 only
                    // doesn't need opening padding, just closing
                    rowString.append(strOfInt);
                    rowString.push_back(' ');
                }
                else
                {
                    // THIS SHOULDNT HAPPEN - an E signifies a problem
                    pushCharCell(rowString, 'E');
                }
            }
            else
            {
                // All other cells get looked up on the board
                pushCharCell(rowString, getCharAt(Cell(row, col), showShips));
            }
        }
        ret.push_back(rowString);
        // add a blank line
        ret.push_back("");
    }

    return ret;
}
