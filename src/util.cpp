#include "util.h"

std::string shipClassLongName(ShipClass sc)
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