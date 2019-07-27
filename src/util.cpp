#include "util.h"

// Cell constructors

// Default to top left corner
Cell::Cell()
{
    row = 1;
    col = 'A';
}

// Automatically turns col into char, e.g. 1 -> 'A', 2 -> 'B', etc.
Cell::Cell(int r, int c)
{
    row = r;
    col = static_cast<char>(c + 64);
}

// Just copies if given as char
Cell::Cell(int r, char c)
{
    row = r;
    col = c;
}

// == overload for Cell
bool Cell::operator==(const Cell &other)
{
    return row == other.row && col == other.col;
}