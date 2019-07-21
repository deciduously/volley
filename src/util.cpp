#include <string>

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
            // We have to catch UBoat here too because it's the same integer value
            // the else block is unreachable
            if (sc == ShipClass::Cruiser)
                return "Cruiser";
            else if (sc == ShipClass::UBoat)
                return "U-Boat";
            else
                return "ERROR: UNKNOWN SHIP CLASS";
            break;
        case Destroyer:
            return "Destroyer";
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
            // We have to catch UBoat here too because it's the same integer value
            // the else block is unreachable
            if (sc == ShipClass::Cruiser)
                return 'C';
            else if (sc == ShipClass::UBoat)
                return 'U';
            else
                return 'E';
            break;
        case Destroyer:
            return 'D';
            break;
    }
    // if we got past the switch, something bad happened because it's exhaustive for that enum
    // Unreachable
    return 'E';
}
