#include <algorithm>
#include <iostream>
#include <limits>

#include "player.h"

//
// HELPER FUNCTIONS
//

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
    return (c >= 'A' && c <= 'z');
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

//
// PRIVATE METHODS
//

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
        string originStr;
        cout << "Origin, as ColRow (e.g \"A1\")> ";
        cin >> originStr;

        // try to get a tuple from the input
        // if we fail - it's not an int and a char in either order - loop again
        int row = 0;
        char col = 'Z';
        if (originStr.size() > 3 || originStr.size() < 2)
        {
            cout << "Please only enter two - three characters, a letter column and an integer row" << endl;
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

// Returns a random origin for a given ShipClass guaranteed to work in at least one direction
cell Player::getRandomOrigin(ShipClass sc)
{
    // Declare return value
    cell ret = {0, ' '};

    do
    {
        // get two random numbers between 1 and 10
        int row = rand() % 10 + 1;
        int colNum = rand() % 10 + 1;

        // store as a cell
        ret = {row, colNum + 64};

        // move on if it fits either way - placement will handle choosing a direction
    } while (!board.doesFit(ret, sc.variant(), Direction::Left) && !board.doesFit(ret, sc.variant(), Direction::Down));

    return ret;
}

// Helper method to prompt user a single ship input
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
        // if there's only one left, autoselect it
        if (unassignedShips.size() == 1)
        {
            cout << "One ship left: placing " << unassignedShips[0].toString() << endl;
            return unassignedShips[0];
        }

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

// Places a ship
void Player::placeShip(cell o, ShipClass sc, Direction d)
{
    // This function does not validate whether it can first!
    // The input function should have done that.
    // Push it to the board
    board.pushShip(Ship(o, sc, d));
    // Remove it from unassignedShips
    // find the idx
    int toDelIdx = unassignedShips.size();
    int maxSize = toDelIdx;
    for (int i = 0; i < maxSize; i++)
    {
        if (unassignedShips[i].eqVariant(sc))
        {
            toDelIdx = i;
            break;
        }
    }
    // erase if found
    if (toDelIdx < maxSize)
    {
        unassignedShips.erase(unassignedShips.begin() + toDelIdx);
    }
}

//
// PROTECTED METHODS
//

// Randomly choose placements for all remaining unassigned ships
// Computer always uses this, player is given the option at each ship placement to do for the rest
void Player::randomlyPlaceShips()
{
    int shipsSize = unassignedShips.size();
    for (int i = 0; i < shipsSize; i++)
    {
        // always act on unassignedShips[0]
        // placeShip will remove it, so the next time through it will be a new ship
        ShipClass currentShipClass = unassignedShips[0];

        // each ship, randomly pick an origin
        cell origin = getRandomOrigin(currentShipClass);
        // then do the doesFit check, and if necessary randomly choose a direction
        // no need to be removing ships as we go
    }
}

//
// PUBLIC METHODS
//

// Constructor
Player::Player(int boardSize)
{
    board = Board(boardSize);
    unassignedShips = {AircraftCarrier, Battleship, Cruiser, Destroyer, UBoat};
}

// Return the board output as a vector of strings, one per line
lines Player::toLineStrings()
{
    // add "Player"  - or "Computer" ? -  header
    lines ret = {};

    // 15 spaces left, 11 right
    std::string headerLine = "               Player           ";

    ret.push_back(headerLine);
    ret.push_back("");
    // insert board line strings
    lines boardLines = board.toLineStrings(true);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}

// Return the board output as a single multiline string
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

// Run the placement loop to prompt user for ship locations
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
outer:
    while (unassignedShips.size() > 0)
    {
        // display board
        cout << toString();

        // Prompt user for which ship to place
        ShipClass shipChoice = getShipClass();
        cout << "Placing " << shipChoice.toString() << "." << endl;

        // Prompt user for origin
        cell origin = getOrigin(shipChoice);
        cout << "Row: " << get<0>(origin) << " Col: " << get<1>(origin) << endl;

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
            cout << shipChoice.toString() << " only fits left.  Saving..." << endl;
            // technically no need to set, it should be Left already, but just in case
            d = Direction::Left;
        }
        else if (!fitsLeft && fitsDown)
        {
            // must be Down - inform the user
            cout << shipChoice.toString() << " only fits down.  Saving..." << endl;
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
                if (directionChoice == 'L' || directionChoice == 'D')
                {
                    if (directionChoice == 'L')
                    {
                        d = Direction::Left;
                        break;
                    }
                    else if (directionChoice == 'D')
                    {
                        d = Direction::Down;
                        break;
                    }
                }
                else
                {
                    cout << "Please enter \"L\" or \"D\"." << endl;
                    continue;
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

        // Confirm triple

        char confirmChoice = 'x';
        bool startOver = false;
        for (;;)
        {
            //TODO first, show the board with the ship placed - a Board::removeShip method would be good
            // not urgent

            // build origin string
            std::string originStr = "";
            originStr.push_back(get<1>(origin));
            originStr.append(std::to_string(get<0>(origin)));

            // display all three choices
            cout << "Origin: " << originStr << endl
                 << "Class: " << shipChoice.toString() << " (Length: " << shipChoice.size() << ")" << endl
                 << "Direction: " << directionString << endl
                 << "Confirm? (Y/N)> ";
            cin >> confirmChoice;
            confirmChoice = toupper(confirmChoice);
            if (confirmChoice != 'Y')
            {
                cout << "Starting over!" << endl;
                goto outer;
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
