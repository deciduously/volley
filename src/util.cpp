#include <cstdlib>
#include <iostream>

#include "util.h"

// Pretty-print the ShipClass enum in long-form text
std::string shipClassString(ShipClass sc)
{
    switch (sc)
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
    }
    // if we got past the switch, something bad happened because it's exhaustive for that enum
    // Unreachable
    return "ERROR: UNKNOWN SHIP CLASS";
}

// Get the corresponding char for each ShipClass variant
char shipClassChar(ShipClass sc)
{
    switch (sc)
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
    }
    // if we got past the switch, something bad happened because it's exhaustive for that enum
    // Unreachable
    return 'E';
}

// Get the corresponding length for each ShipClass variant
int shipLength(ShipClass sc)
{
    switch (sc)
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
    }
    // if we got past the switch, something bad happened because it's exhaustive for that enum
    // Unreachable
    return -1;
}

// Get a ShipClass from a char
ShipClass charToShipClass(char c)
{
    switch (toupper(c))
    {
    case 'A':
        return ShipClass::AircraftCarrier;
        break;
    case 'B':
        return ShipClass::Battleship;
        break;
    case 'C':
        return ShipClass::Cruiser;
        break;
    case 'D':
        return ShipClass::Destroyer;
        break;
    case 'U':
        return ShipClass::UBoat;
        break;
    }
    // Panic if something unexpected comes through here
    // TODO maybe not panic?  I don't think anything unexpected will come through here
    std::cout << "Invalid chip class" << std::endl;
    exit(1);
}