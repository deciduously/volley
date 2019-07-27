#include <algorithm>

#include "board.h"

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
    ships = {};
}

// Check if a shipPlacement would fit on the board before creating a Ship
bool Board::doesFit(Cell o, ShipClass sc, Direction d)
{
    // check each cell the ship would occupy
    // build the hypthetical ship and store its contained cells
    Ship testShip = Ship(o, sc, d);
    std::vector<Cell> cells = testShip.containedCells();
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
char Board::getCharAt(Cell c, bool showShips)
{
    using std::find;
    using std::vector;

    // if row or col out of bounds, return 'E'
    if (c.row < 1 || c.row > dimension || c.col < 'A' || c.col > ('A' + dimension))
    {
        return 'E';
    }

    // init return value to default (empty)
    char ret = '.';

    // If we're displaying the ships, run that check
    if (showShips)
    {
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
                switch (ship.getShipClass().sct)
                {
                case ShipClassType::AircraftCarrier:
                    ret = 'A';
                    break;
                case ShipClassType::Battleship:
                    ret = 'B';
                    break;
                case ShipClassType::Cruiser:
                    ret = 'C';
                    break;
                case ShipClassType::Destroyer:
                    ret = 'D';
                    break;
                case ShipClassType::UBoat:
                    ret = 'U';
                    break;
                case ShipClassType::Unknown:
                    ret = 'E';
                    break;
                }
            }
        }
    }
    return ret;
}

// Add a ship to the board
void Board::pushShip(Ship s)
{
    ships.push_back(s);
}

// Getter for board dimension
int Board::size()
{
    return dimension;
}

// Returns a vector of strings, one for each line of this board
// pass true to show ship locations, false to only show hits/misses
lines Board::toLineStrings(bool showShips)
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
