#include <cstdlib>
#include <iostream>

#include "shipClass.h"

//
// PUBLIC METHODS
//

// Default constructor
ShipClass::ShipClass()
{
    sct = ShipClassType::Unknown;
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
bool ShipClass::eqVariant(ShipClass other)
{
    return sct == other.variant();
}

// Get the corresponding length for each ShipClass variant
int ShipClass::size()
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
char ShipClass::toChar()
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
std::string ShipClass::toString()
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

// Getter for ShipClassType
ShipClassType ShipClass::variant()
{
    return sct;
}
