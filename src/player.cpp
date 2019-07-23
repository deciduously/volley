#include <algorithm>
#include <iostream>
#include <limits>

#include "player.h"

// Helper function to pretty-print the vector of shipclasses
std::string shipClassString(std::vector<ShipClass> scs)
{
    using std::string;
    using std::to_string;

    // Open string with a bracket
    string ret = "{ ";

    // Iterate through the unassigned ships, adding them to the output
    int unassignedShipsSize = scs.size();
    for (int i = 0; i < unassignedShipsSize; i++)
    {
        ShipClass sc = scs[i];
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

Player::Player(int boardSize)
{
    board = Board(boardSize);
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

// Helper function to get a single ship input
char getShipLetter(std::vector<ShipClass> validChoices)
{
    // <iostream>
    using std::cin;
    using std::cout;
    using std::endl;

    // <algorithm>
    using std::find;

    // <limits>
    using std::numeric_limits;
    using std::streamsize;

    // <string> (via util.h)
    using std::string;

    // <vector> (via util.h)
    using std::vector;

    char ret = ' ';
    string shipTypeInput;
    for (;;)
    {
        cout << "\n\nWhich ship do you want to add? Select letter: " << shipClassString(validChoices) << "> ";

        cin >> shipTypeInput;
        // it was a character, check if it was an option
        // if it was longer than one character, it's invalid
        if (shipTypeInput.size() > 1)
        {
            std::cout << "Please just enter a single letter";
            cin.clear();
            // ignore rest of current line, up to newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // First, build a std::vector of the char representations of the ships available
        vector<char> unassignedShipLettersVec = {};
        int unassignedShipsLen = validChoices.size();
        for (int i = 0; i < unassignedShipsLen; i++)
            unassignedShipLettersVec.push_back(shipClassChar(validChoices[i]));

        ret = toupper(shipTypeInput[0]);

        if (find(unassignedShipLettersVec.begin(), unassignedShipLettersVec.end(), ret) != unassignedShipLettersVec.end())
            // if the input can be found inside the vector of all of them, return it
            return ret;
        else
            // They picked something not in the list, try again
            cout << "Not an available ship!";
    }
}

void Player::runPlacement()
{
    // <iostream>
    using std::cout;
    using std::endl;

    // Continually prompt to place ships until there are none left
    while (unassignedShips.size() > 0)
    {
        // display board
        std::cout << toString();

        // Prompt user for which ship to place
        char shipChoice = getShipLetter(unassignedShips);
        cout << shipChoice << endl;
    }
}
