#include <iostream>
#include <string>

#include "board.h"

// Helper function to get the proper row letter
char rowLetter(int i)
{
    return i + 65;
}

// Helper function to add a cell to a string with padding from a char
void pushCharCell(std::string &s, char contents)
{
    s.push_back(' ');
    s.push_back(contents);
    s.push_back(' ');
}

// Helper function to add a cell to a string with padding
void pushStrCell(std::string &s, std::string contents)
{
    s.push_back(' ');
    s.append(contents);
    s.push_back(' ');
}

// Board constructor
Board::Board()
{
    size = 10; // All boards are 10 (A-J)
}

// TODO use sprintf for all of it instead of homebrew helpers?
// Returns a vector of strings, one for each line of this board
std::vector<std::string> Board::toLineStrings()
{
    // Return vector
    std::vector<std::string> ret = {};

    // Write the header column labels
    std::string headerLine = "";
    for (int i = 0; i < size; i++)
    {
        // first one should be blank
        if (i == 0)
            pushCharCell(headerLine, ' ');
        else
        {   
            // use snprintf to convert the integer to a string
            char buffer [33];
            snprintf(buffer, sizeof(buffer), "%d", i);
            // add that result to the return string
            std::string intStr = buffer;
            pushStrCell(headerLine, intStr);
        }
    }
    ret.push_back(headerLine);

    // add a blank lines
    ret.push_back("");

    // then, write the grid
    // first cell of each row is the row letter
    for (int row = 0; row < size; row++)
    {
        std::string rowString = "";
        for (int col = 0; col < size; col++)
        {
            if (col == 0)
                pushCharCell(rowString, rowLetter(row));
            else
                pushCharCell(rowString, '_'); // TODO get actual character based on ships
        }
        ret.push_back(rowString);
        // add a blank line
        ret.push_back("");
    }

    return ret;
}