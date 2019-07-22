#include <iostream>

#include "player.h"

std::string Player::unassignedShipLetters()
{
    using std::string;
    using std::to_string;

    // Open string with a bracket
    string ret = "{ ";

    // Iterate through the unassigned ships, adding them to the output
    int unassignedShipsSize = unassignedShips.size();
    for (int i = 0; i < unassignedShipsSize; i++)
    {
        ShipClass sc = unassignedShips[i];
        ret.push_back(shipClassChar(sc));
        ret.push_back(':');
        ret.push_back(to_string(shipLength(sc))[0]);
        ret.push_back(' ');
    }

    // Add closing brace and return result
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
    // No other state to display?
    // TODO add "Player" or "Computer" header
    return board.toLineStrings();
}

std::string Player::toString()
{
    // put together a single string from the contents of Player::toLineStrings()
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
    using std::cout;
    using std::cin;

    // Continually prompt to place ships until there are none left
    while (unassignedShips.size() > 0)
    {
        // display board
        cout << toString();

        // get ship type
        char shipTypeInput;
        cout << "\n\nWhich ship do you want to add? " << unassignedShipLetters() << ": ";
        cin >> shipTypeInput;

        // validate input.
        // needs to be a character
        // then needs to be one of the options
    }
}
