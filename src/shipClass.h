/*
* shipClass
* This class holds getter methods for */
#ifndef __SHIPCLASS_H_INCLUDED
#define __SHIPCLASS_H_INCLUDED

#include "util.h"

enum ShipClassType
{
    AircraftCarrier,
    Battleship,
    Cruiser,
    Destroyer,
    UBoat,
    Unknown
};

class ShipClass
{
    ShipClassType type;

public:
    // Constructors
    ShipClass();
    ShipClass(ShipClassType sc);
    ShipClass(char c);

    // Methods
    char toChar();
    int size();
    std::string toString();
};
#endif