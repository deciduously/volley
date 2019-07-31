#include <algorithm>
#include <iostream>

#include "board.h"

// Helper function to determine if a char is a letter
bool isLetter(char c)
{
    // 65 = 'A', 90 = 'z'
    return (c >= 'A' && c <= 'z');
}

// Helper function to add a cell to a string with padding from a char
void pushCharCell(std::string &s, char contents)
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
bool Board::doesFit(ShipPlacement sp) const
{
    // check each cell the ship would occupy
    // build the hypthetical ship and store its contained cells
    std::vector<Cell> cells = sp.containedCells();
    int cellsSize = cells.size();
    for (int i = 0; i < cellsSize; i++)
    {
        if (getCharAt(cells[i], true) != '.')
        {
            return false;
        }
    }
    return true;
}

// Returns the corresponding cell character
// Pass true to show ship locations, false to only show hits/misses
char Board::getCharAt(Cell c, bool showShips) const
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

    int shipsSize = ships.size();

    // loop through ships
    for (int i = 0; i < shipsSize; i++)
    {
        Ship ship = ships[i];
        // each ship, loop through the contained cells
        vector<Cell> cells = ship.containedCells();

        // if any of them are found in cells, set ret to that ship character
        // runPlacement should have avoided any overlaps
        if (find(cells.begin(), cells.end(), c) != cells.end())
        {
            ret = ship.getShipClass().toChar();
        }
    }

    // Overlay hits and misses
    if (find(receivedShots.begin(), receivedShots.end(), c) != receivedShots.end())
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
    } while (std::find(getAllShots().begin(), getAllShots().end(), ret) != getAllShots().end());
    return ret;
}

// Method to prompt the user for a cell, ensuring its a valid spot on this board
// Returning a default cell indicates 'R', or random
Cell Board::promptCell(const std::string &promptStr) const
{
    using std::cerr;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    for (;;)
    {
        //prompt for input
        string originStr;
        cout << "Enter " << promptStr << ".  Enter 'R' for random.  (ColRow, e.g. \"A1\" or \"a1\")> ";
        cin >> originStr;

        // catch random
        if (originStr.size() == 1 && toupper(originStr[0]) == 'R')
        {
            cout << "Rolling the dice..." << endl;
            return getRandomTarget();
        }

        // try to get a tuple from the input
        // if we fail - it's not an int and a char in either order - loop again
        int row = 0;
        char col = 'Z';
        if (originStr.size() > 3 || originStr.size() < 2)
        {
            cerr << "Please only enter two - three characters, a letter column and an integer row" << endl;
            clearCin();
            continue;
        }

        // check if the first one is a letter
        if (isLetter(originStr[0]))
            col = toupper(originStr[0]);
        else
        {
            cerr << "Please enter a letter as the first character" << endl;
            clearCin();
            continue;
        }

        // store the rest as the number
        try
        {
            row = stoi(originStr.substr(1, originStr.size() - 1));
        }
        catch (const std::invalid_argument &ia)
        {
            cerr << "Please enter a number as the rest of your input." << endl;
            clearCin();
            continue;
        }

        // ensure it's a valid spot on the board
        if (row < 1 || row > size())
        {
            cerr << "Invalid row!" << endl;
            clearCin();
            continue;
        }
        else if (col < 65 || col >= 'A' + size())
        {
            cerr << "Invalid column!" << endl;
            clearCin();
            continue;
        }
        else
        {
            Cell ret = Cell(row, col);
            // if it fits, check if it's taken
            if (std::find(getAllShots().begin(), getAllShots().end(), ret) != getAllShots().end())
            {
                cout << "That's taken!" << endl;
                clearCin();
                continue;
            }
            else
            {
                return Cell(row, col);
            }
        }
    }
}

// Add a ship to the board
void Board::pushShip(Ship s)
{
    ships.push_back(s);
}

// Get all recorded hits and misses
std::vector<Cell> Board::getAllShots() const
{
    return receivedShots;
}

// Receive a shot at a cell, return true if it's a hit
bool Board::receiveShot(Cell target)
{
    char result = getCharAt(target, true);
    receivedShots.push_back(target);
    bool ret = result != '.';
    // record hit if true
    if (ret)
    {
        int shipsSize = ships.size();
        for (int i = 0; i < shipsSize; i++)
        {
            Ship ship = ships[i];
            if (result == ship.getShipClass().toChar())
            {
                ships[i].takeHit();
            }
        }
    }
    return ret;
}

// get how many ships still have health
int Board::remainingShipsCount() const
{
    // Before we've started, there are no ships
    // This means we're in Placement, return the total number of ships
    int shipsLen = ships.size();
    if (shipsLen == 0)
        return 5;

    int ret = 0;
    for (int i = 0; i < shipsLen; i++)
    {
        if (ships[i].getHits() > 0)
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
    int shipsLen = ships.size();
    if (shipsLen == 0)
        return {ShipClass(AircraftCarrier), ShipClass(Battleship), ShipClass(Cruiser), ShipClass(Destroyer), ShipClass(UBoat)};

    std::vector<ShipClass> ret = {};
    for (int i = 0; i < shipsLen; i++)
    {
        if (ships[i].getHits() > 0)
        {
            ret.push_back(ships[i].getShipClass());
        }
    }
    return ret;
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
