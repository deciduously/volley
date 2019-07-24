#include <algorithm>
#include <iostream>
#include <limits>

#include "player.h"

// Helper function to clear out cin to loop for input again
void clearCin()
{
    std::cin.clear();
    // ignore rest of current line, up to newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Helper function to determine if a char is a letter
bool isLetter(char c)
{
    return (c >= 65 && c <= 90);
}

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
ShipClass Player::getShipClass()
{
    // <iostream>
    using std::cin;
    using std::cout;
    using std::endl;

    // <algorithm>
    using std::find;

    // <string> (via util.h)
    using std::string;

    // <vector> (via util.h)
    using std::vector;

    char ret = ' ';
    string shipTypeInput;
    for (;;)
    {
        cout << "\n\nWhich ship do you want to add? Select letter: " << shipClassString(unassignedShips) << "> ";

        cin >> shipTypeInput;
        // it was a character, check if it was an option
        // if it was longer than one character, it's invalid
        if (shipTypeInput.size() > 1)
        {
            std::cout << "Please just enter a single letter";
            clearCin();
            continue;
        }
        // First, build a std::vector of the char representations of the ships available
        vector<char> unassignedShipLettersVec = {};
        int unassignedShipsLen = unassignedShips.size();
        for (int i = 0; i < unassignedShipsLen; i++)
            unassignedShipLettersVec.push_back(shipClassChar(unassignedShips[i]));

        ret = toupper(shipTypeInput[0]);

        if (find(unassignedShipLettersVec.begin(), unassignedShipLettersVec.end(), ret) != unassignedShipLettersVec.end())
            // if the input can be found inside the vector of all of them, return it
            return charToShipClass(ret);
        else
        // They picked something not in the list, try again
        {
            cout << "Not an available ship!";
            clearCin();
        }
    }
}

// Helper method to prompt user for origin
origin Player::getOrigin(ShipClass sc)
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    // Instantiate return string
    string ret = "";

    for (;;)
    {
        //prompt for input
        string originStr;
        cout << "Origin (e.g \"A1\" or \"1A\")> ";
        cin >> originStr;

        // try to get a tuple from the input
        // if we fail - it's not an int and a char in either order - loop again
        int row = 0;
        char col = 'Z';
        if (originStr.size() != 2)
        {
            cout << "Please only enter two characters, an int row and a letter column" << endl;
            clearCin();
            continue;
        }

        // TODO store the input
        // What you had last night broke for row 10.
        // what you need to do is search for a letter and extract it
        // and try to save the rest as the number
        // check if the first one is a letter

        // ensure it's a valid spot on the board
        if (row < 1 || row > 10)
        {
            cout << "Invalid row!" << endl;
            clearCin();
            continue;
        }
        if (col < 65 || col > 74) // A < col < J
        {
            cout << "Invalid column!" << endl;
            clearCin();
            continue;
        }

        // Return the result as a literal
        return {row, col};
    }
}

// Places a ship
void Player::placeShip(origin o, ShipClass sc, Direction d)
{
    d = Direction::Left;
    o = {1, 3};
    std::cout << shipClassString(sc);
    // This function does not validate whether it can first!
    // The input function should have done that.
}

void Player::runPlacement()
{
    // <iostream>
    using std::cout;
    using std::endl;

    // <string>
    using std::string;

    // Continually prompt to place ships until there are none left
    while (unassignedShips.size() > 0)
    {
        // display board
        std::cout << toString();

        // Prompt user for which ship to place
        ShipClass shipChoice = getShipClass();
        cout << shipChoice << endl;

        // Prompt user for origin
        origin origin = getOrigin(shipChoice);

        // Prompt user for direction

        // Place ship
        placeShip(origin, shipChoice, Direction::Left);
    }
}
