#include <iostream>
#include <iterator>
#include <limits>

#include "util.h"

// Helper function to clear out cin to loop for input again
void clearCin()
{
    std::cin.clear();
    // ignore rest of current line, up to newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ostream overload for Direction
std::ostream &operator<<(std::ostream &stream, const Direction &d)
{
    if (d == Direction::Left)
    {
        return stream << "Left";
    }
    else
    {
        return stream << "Down";
    }
}

// ostream overload for lines
std::ostream &operator<<(std::ostream &stream, const lines &l)
{
    if (!l.empty())
    {
        std::copy(l.begin(), l.end(), std::ostream_iterator<std::string>(stream, "\n"));
    }
    return stream;
}

//
// Cell
//

// Default to top left corner
Cell::Cell()
{
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
bool Cell::operator==(const Cell &other) const
{
    return row == other.row && col == other.col;
}

// Prettyprint
std::string Cell::toString() const
{
    std::string ret = "Row: ";
    ret += std::to_string(row);
    ret += " Col: ";
    ret.push_back(col);
    return ret;
}

// Stream overload
std::ostream &operator<<(std::ostream &stream, const Cell &c)
{
    return stream << c.toString();
}

//
// ShipClass
//

// Default constructor
ShipClass::ShipClass()
{
}

// Construct a ShipClass from a char
ShipClass::ShipClass(char c)
{
    switch (toupper(c))
    {
    case 'A':
        sct = ShipClassType::AircraftCarrier;
        break;
    case 'B':
        sct = ShipClassType::Battleship;
        break;
    case 'C':
        sct = ShipClassType::Cruiser;
        break;
    case 'D':
        sct = ShipClassType::Destroyer;
        break;
    case 'U':
        sct = ShipClassType::UBoat;
        break;
    default:
        sct = ShipClassType::Unknown;
    }
}

// Construct a ShipClass from ShipClassType
ShipClass::ShipClass(ShipClassType sc)
{
    sct = sc;
}

// Check if this ShipClass has the same variant as other ShipClass
bool ShipClass::operator==(const ShipClass &other) const
{
    return sct == other.sct;
}

// Get the corresponding length for each ShipClass variant
int ShipClass::size() const
{
    switch (sct)
    {
    case AircraftCarrier:
        return 5;
        break;
    case Battleship:
        return 4;
        break;
    case Cruiser:
        return 3;
        break;
    case Destroyer:
        return 2;
        break;
    case UBoat:
        return 3;
        break;
    case Unknown:
        return 0;
        break;
    }
    // if we got past the switch, something bad happened because it's exhaustive for that enum
    // Unreachable
    return -1;
}

// Get the corresponding char for each ShipClass variant
char ShipClass::toChar() const
{
    switch (sct)
    {
    case AircraftCarrier:
        return 'A';
        break;
    case Battleship:
        return 'B';
        break;
    case Cruiser:
        return 'C';
        break;
    case Destroyer:
        return 'D';
        break;
    case UBoat:
        return 'U';
        break;
    case Unknown:
        return 'E';
    }
    // if we got past the switch, something bad happened because it's exhaustive for that enum
    // Unreachable
    return 'E';
}

// Pretty-print the ShipClass enum in long-form text
std::string ShipClass::toString() const
{
    switch (sct)
    {
    case AircraftCarrier:
        return "Aircraft Carrier";
        break;
    case Battleship:
        return "Battleship";
        break;
    case Cruiser:
        return "Cruiser";
        break;
    case Destroyer:
        return "Destroyer";
        break;
    case UBoat:
        return "U-Boat";
        break;
    case Unknown:
        return "Unknown Ship Class";
        break;
    }
    // if we got past the switch, something bad happened because it's exhaustive for that enum
    // Unreachable
    return "ERROR: UNKNOWN SHIP CLASS";
}

// Stream overload
std::ostream &operator<<(std::ostream &stream, const ShipClass &sc)
{
    return stream << sc.toString();
}