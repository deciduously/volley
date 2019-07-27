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
    ShipClassType sct;

public:
    // Constructors
    ShipClass();
    ShipClass(char c);
    ShipClass(ShipClassType sc);

    // Methods
    bool eqVariant(ShipClass other);
    int size();
    char toChar();
    std::string toString();
    ShipClassType variant();
};
#endif