#include <cstdlib>
#include <iostream>

#include "shipClass.h"

// Default constructor
ShipClass::ShipClass()
{
    type = ShipClassType::Unknown;
}

// ShipClass from ShipClassType
ShipClass::ShipClass(ShipClassType sc)
{
    type = sc;
}

// Get a ShipClass from a char
ShipClass::ShipClass(char c)
{
    switch (toupper(c))
    {
    case 'A':
        type = ShipClassType::AircraftCarrier;
        break;
    case 'B':
        type = ShipClassType::Battleship;
        break;
    case 'C':
        type = ShipClassType::Cruiser;
        break;
    case 'D':
        type = ShipClassType::Destroyer;
        break;
    case 'U':
        type = ShipClassType::UBoat;
        break;
    default:
        type = ShipClassType::Unknown;
    }
}

// Pretty-print the ShipClass enum in long-form text
std::string ShipClass::toString()
{
    switch (type)
    {
    case AircraftCarrier:
        return "Carrier";
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

// Get the corresponding char for each ShipClass variant
char ShipClass::toChar()
{
    switch (type)
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

// Get the corresponding length for each ShipClass variant
int ShipClass::size()
{
    switch (type)
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