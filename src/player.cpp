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
    // 65 = 'A', 90 = 'z'
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
        ret.push_back(sc.toChar());
        ret.push_back(':');
        ret.push_back(to_string(sc.size())[0]);
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
            unassignedShipLettersVec.push_back(unassignedShips[i].toChar());

        ret = toupper(shipTypeInput[0]);

        if (find(unassignedShipLettersVec.begin(), unassignedShipLettersVec.end(), ret) != unassignedShipLettersVec.end())
            // if the input can be found inside the vector of all of them, return it
            return ShipClass(ret);
        else
        // They picked something not in the list, try again
        {
            cout << "Not an available ship!";
            clearCin();
        }
    }
}

// Helper method to prompt user for origin
cell Player::getOrigin(ShipClass sc)
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
        // TODO accept either RowCol or ColRow - trickier because of 10
        string originStr;
        cout << "Origin, as RowCol (e.g \"A1\")> ";
        cin >> originStr;

        // try to get a tuple from the input
        // if we fail - it's not an int and a char in either order - loop again
        int row = 0;
        char col = 'Z';
        if (originStr.size() != 2)
        {
            cout << "Please only enter two characters, a letter column and an integer row" << endl;
            clearCin();
            continue;
        }

        // check if the first one is a letter
        if (isLetter(originStr[0]))
            col = toupper(originStr[0]);
        else
        {
            cout << "Please enter a letter as the first character" << endl;
            clearCin();
            continue;
        }

        // store the rest as the number
        row = stoi(originStr.substr(1, originStr.size() - 1));

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

        // Return the result as a literal if it fits, or loop again
        // TODO add the doesFit check here.
        sc = ShipClass(ShipClassType::AircraftCarrier); // remove!!
        return {row, col};
    }
}

// Places a ship
void Player::placeShip(cell o, ShipClass sc, Direction d)
{
    // This function does not validate whether it can first!
    // The input function should have done that.
    // Just push it to the board
    board.pushShip(Ship(o, sc, d));
}

void Player::runPlacement()
{
    // <iostream>
    using std::cin;
    using std::cout;
    using std::endl;
    using std::get;
    using std::make_tuple;

    // <string>
    using std::string;

    // Continually prompt to place ships until there are none left
    while (unassignedShips.size() > 0)
    {
        // display board
        cout << toString();

        // TODO - confirm each with a loop - generalize that.

        // Prompt user for which ship to place
        ShipClass shipChoice = getShipClass();
        cout << "Placing " << shipChoice.toString() << "." << endl;

        // Prompt user for origin
        cell origin = getOrigin(shipChoice);
        cout << "Row: " << get<1>(origin) << " Col: " << get<0>(origin) << endl;

        // get direction - default to Left arbitrarily
        Direction d = Direction::Left;

        // Check if the ship fits either way
        // If it fits one way or the other, set the direction automatically
        // If both work, prompt to choose
        bool fitsLeft = board.doesFit(origin, shipChoice.variant(), Direction::Left);
        bool fitsDown = board.doesFit(origin, shipChoice.variant(), Direction::Down);
        if (!fitsLeft && !fitsDown)
        {
            // Can't possibly place with that origin
            // Tell them it's gonna be left or down, try again
            cout << "Cannot place " << shipChoice.toString() << " at that location." << endl
                 << "You will orient Left or Down from the origin.  Please pick a new origin." << endl;
            continue;
        }
        else if (fitsLeft && !fitsDown)
        {
            // must be Left - inform the user
            cout << shipChoice.toString() << " only fits left.  Saving...";
            // technically no need to set, it should be Left already, but just in case
            d = Direction::Left;
        }
        else if (!fitsLeft && fitsDown)
        {
            // must be Down - inform the user
            cout << shipChoice.toString() << " only fits down.  Saving...";
            d = Direction::Down;
        }
        else
        {
            // it fits both ways, prompt
            char directionChoice = 'x';
            for (;;)
            {
                cout << "(L)eft or (D)own> ";
                cin >> directionChoice;
                directionChoice = toupper(directionChoice);
                if (directionChoice != 'L' && directionChoice != 'D')
                {
                    cout << "Please enter \"L\" or \"D\"." << endl;
                    continue;
                }
                else if (directionChoice == 'L')
                {
                    d = Direction::Left;
                }
                else if (directionChoice == 'D')
                {
                    d = Direction::Down;
                }
            }
        }

        // Pretty-print direction string
        std::string directionString = "";
        if (d == Direction::Left)
        {
            directionString.append("Left");
        }
        else
        {
            // only one other option...
            directionString.append("Down");
        }
        cout << "Direction: " << directionString << endl;

        // Confirm triple

        char confirmChoice = 'x';
        bool startOver = false;
        for (;;)
        {
            //TODO first, show the board with the ship placed - a Board::removeShip method would be good
            // not urgent

            // build origin string
            std::string originStr = "";
            originStr.append(std::to_string(get<0>(origin)));
            originStr.push_back(get<1>(origin));

            // display all three choices
            cout << "Origin: " << originStr << " Class: " << shipChoice.toString() << " Direction: " << directionString << ".  Confirm? (Y/N)> " << endl;
            cin >> confirmChoice;
            confirmChoice = toupper(confirmChoice);
            if (confirmChoice != 'Y')
            {
                // TODO allow to adjust just one.
                cout << "Starting over!" << endl;
                continue;
            }
            else
            {
                cout << "Confirmed!" << endl;
                break;
            }
        }

        // If the user didn't hit Y, start over
        if (startOver)
            break;

        // Otherwise place ship
        cout << "Placing ship..." << endl;
        placeShip(origin, shipChoice, d);
    }
}
