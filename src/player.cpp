#include <iostream>

#include "player.h"

std::string Player::unassignedShipLetters()
{
    std::string ret = "{ ";
    int unassignedShipsSize = unassignedShips.size();
    for (int i = 0; i < unassignedShipsSize; i++)
    {
        ShipClass sc = unassignedShips[i];
        ret.push_back(shipClassChar(sc));
        ret.push_back(':');
        ret.push_back(std::to_string(shipLength(sc))[0]);
        ret.push_back(' ');
    }
    ret.push_back('}');
    return ret;
}

// PUBLIC

Player::Player()
{
    unassignedShips = {AircraftCarrier, Battleship, Cruiser, Destroyer, UBoat};
}
lines Player::toLineStrings()
{
    return board.toLineStrings();
}

std::string Player::toString()
{
    std::string ret = "";
    lines lineStrings = toLineStrings();
    int lineStringsSize = lineStrings.size();
    for (int i = 0; i < lineStringsSize; i++)
    {
        ret.append(lineStrings[i]);
        ret.push_back('\n');
    }
    return ret;
}

void Player::runPlacement()
{
    while (unassignedShips.size() > 0)
    {
        // display board
        std::cout << toString();

        // get ship type
        // TODO print the options {A B C D U}
        char shipTypeInput;
        std::cout << "\n\nWhich ship do you want to add? " << unassignedShipLetters() << ": ";
        std::cin >> shipTypeInput;
    }
}
