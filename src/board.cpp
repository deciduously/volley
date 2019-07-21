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
    // first cell of each row is the row number
    for (int row = 1; row <= size; row++)
    {
        std::string rowString = "";
        for (int col = 0; col < size; col++)
        {
            if (col == 0)
                pushCharCell(rowString, std::to_string(row)[0]);
            else
                pushCharCell(rowString, '_'); // TODO get actual character based on ships
        }
        ret.push_back(rowString);
        // add a blank line
        ret.push_back("");
    }

    return ret;
}