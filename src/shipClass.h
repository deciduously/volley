/*
* shipClass
* This class holds getter and printing methods for each of the different types of Ship
* Benjamin Lovy
*/
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
    ShipClassType variant();
    std::string toString();
};
#endif