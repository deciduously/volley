#include <algorithm>
#include <iostream>
#include <limits>

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

void Player::runPlacement()
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

    // <vector> (via util.h)
    using std::vector;

    // Continually prompt to place ships until there are none left
    while (unassignedShips.size() > 0)
    {
        // display board
        cout << toString();

        // get ship type
        char shipTypeInput;

        // Loop until valid input collected
        for (;;)
        {
            cout << "\n\nWhich ship do you want to add? Select letter: " << unassignedShipLetters() << "> ";

            if (cin >> shipTypeInput)
            {
                // it was a character, check if it was an option
                // First, build a std::vector of the char representations of the ships available
                vector<char> unassignedShipLettersVec = {};
                int unassignedShipsLen = unassignedShips.size();
                for (int i = 0; i < unassignedShipsLen; i++)
                    unassignedShipLettersVec.push_back(shipClassChar(unassignedShips[i]));

                if (find(unassignedShipLettersVec.begin(), unassignedShipLettersVec.end(), shipTypeInput) != unassignedShipLettersVec.end())
                    // if the input can be found inside the vector of all of them, break
                    break;
                else
                    // They picked something not in the list, try again
                    cout << "Not an available ship!";
            }
            else
            {
                // wasn't a character
                cout << "Please enter a valid character!" << endl;
                cin.clear();
                // ignore rest of current line, up to newline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}
