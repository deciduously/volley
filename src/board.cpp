#include "board.h"

// Helper function to add a cell to a string with padding from a char
void pushCharCell(std::string &s, char contents)
{
    s.push_back(' ');
    s.push_back(contents);
    s.push_back(' ');
}

// Board constructor
Board::Board()
{
    size = 10; // All boards are 10 (A-J)
}

// TODO use sprintf for all of it instead of homebrew helpers?
// Returns a vector of strings, one for each line of this board
lines Board::toLineStrings()
{
    using std::string;
    using std::to_string;

    // Return vector
    lines ret = {};

    // Write the header column labels
    std::string headerLine = "";
    for (int i = 0; i <= size; i++)
    {
        // first one should be blank
        if (i == 0)
            pushCharCell(headerLine, ' ');
        else
            pushCharCell(headerLine, i + 64);  // get the proper ASCII char
        
    }
    ret.push_back(headerLine);

    // add a blank lines
    ret.push_back("");

    // then, write the grid
    for (int row = 1; row <= size; row++)
    {
        string rowString = "";
        for (int col = 0; col <= size; col++)
        {
            if (col == 0)
            {
                // the first cell of each grid is the row number
                string strOfInt = to_string(row);
                int strLen = strOfInt.size();
                if (strLen == 1)
                {
                    // single-digit numbers can just use pushCharCell
                    pushCharCell(rowString, strOfInt[0]);
                } else if (strLen == 2)
                {
                    // by default this branch handles the 10 only
                    // doesn't need opening padding, just closing
                    rowString.append(strOfInt);
                    rowString.push_back(' ');
                } else {
                    // THIS SHOULDNT HAPPEN - an E signifies a problem
                    pushCharCell(rowString, 'E');
                }
            }
            else
                pushCharCell(rowString, '.'); // TODO get actual character based on ships
        }
        ret.push_back(rowString);
        // add a blank line
        ret.push_back("");
    }

    return ret;
}