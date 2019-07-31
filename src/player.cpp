#include <algorithm>
#include <iostream>

#include "player.h"

//
// PRIVATE METHODS
//

// Helper method to prompt user for origin
Cell Player::getOrigin(ShipClass sc) const
{
    Cell ret = Cell();
    Board b = getBoardConst();

    // Ensure what they pick fits at least one way
    do
    {
        ret = board.promptCell("Origin");
        if (ret == Cell(b.size() + 1, b.size() + 1))
        {
            ret = b.getRandomCell();
        }
    } while (!board.doesFit(ShipPlacement(ret, Direction::Left, sc)) && !board.doesFit(ShipPlacement(ret, Direction::Down, sc)));

    return ret;
}

// Return a random direction for the given origin and shipclass that fit - it's already ensured at least one of the two does
Direction Player::getRandomDirection(Cell origin, ShipClass sc) const
{
    bool fitsLeft = getBoardConst().doesFit(ShipPlacement(origin, Direction::Left, sc));
    bool fitsDown = board.doesFit(ShipPlacement(origin, Direction::Down, sc));
    // don't bother doing the check for if neither work, getRandomOrigin checked it until one or the other did
    if (fitsLeft && !fitsDown)
    {
        return Direction::Left;
    }
    else if (!fitsLeft && fitsDown)
    {
        return Direction::Down;
    }
    else
    {
        // it fits both ways, choose one randomly
        int dirChoice = rand() % 2;
        if (dirChoice == 1)
        {
            return Direction::Left;
        }
        else
        {
            return Direction::Down;
        }
    }
}

// Returns a random origin for a given ShipClass guaranteed to work in at least one direction
Cell Player::getRandomOrigin(ShipClass sc) const
{
    // Declare return value
    Cell ret = Cell();

    do
    {
        ret = board.getRandomCell();
        // move on if it fits either way - placement will handle choosing a direction
    } while (!board.doesFit(ShipPlacement(ret, Direction::Left, sc)) && !board.doesFit(ShipPlacement(ret, Direction::Down, sc)));

    return ret;
}

// Helper method to prompt user a single ship input
ShipClass Player::getShipClass() const
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

        cout << "\n\nWhich ship do you want to add?\nSelect letter, or 'R' to place all the rest randomly: " << remainingShipsStr(GameState::Placement) << "> ";

        cin >> shipTypeInput;
        // it was a character, check if it was an option
        // if it was longer than one character, it's invalid
        if (shipTypeInput.size() > 1)
        {
            std::cout << "Please just enter a single letter";
            clearCin();
            continue;
        }

        // upper case it and store it
        ret = toupper(shipTypeInput[0]);

        // Check if it's r, early return if so
        if (ret == 'R')
        {
            return ret;
        }

        // First, build a std::vector of the char representations of the ships available
        vector<char> unassignedShipLettersVec = {};
        int unassignedShipsLen = unassignedShips.size();
        for (int i = 0; i < unassignedShipsLen; i++)
            unassignedShipLettersVec.push_back(unassignedShips[i].toChar());

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
void Player::placeShip(ShipPlacement sp)
{
    // This function does not validate whether it can first!
    // The input function should have done that.
    // Push it to the board
    board.pushShip(Ship(sp));
    // Remove it from unassignedShips
    // find the idx
    int toDelIdx = unassignedShips.size();
    int maxSize = toDelIdx;
    for (int i = 0; i < maxSize; i++)
    {
        if (unassignedShips[i] == sp.shipClass)
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

        // each ship, randomly pick a valid origin and direction
        Cell origin = getRandomOrigin(currentShipClass);
        Direction d = getRandomDirection(origin, currentShipClass);

        // plop it on the board
        placeShip(ShipPlacement(origin, d, currentShipClass));
    }
}

int Player::remainingShipsCount() const
{
    return board.remainingShipsCount();
}

// Helper function to pretty-print the vector of shipclasses
std::string Player::remainingShipsStr(const GameState gs) const
{
    using std::string;
    using std::to_string;

    // grab which ship vector to use
    std::vector<ShipClass> toShow;

    switch (gs)
    {
    case GameState::Placement:
        toShow = unassignedShips;
        break;
    case GameState::Firing:
        toShow = getBoardConst().remainingShips();
        break;
    case GameState::GameOver:
        std::cerr << "Something weird and unexpected has happened" << std::endl;
        std::exit(1);
        break;
    }

    // Open string with a bracket
    string ret = "{ ";

    // Iterate through the unassigned ships, adding them to the output
    int vecSize = toShow.size();
    for (int i = 0; i < vecSize; i++)
    {
        ShipClass sc = toShow[i];
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
// PUBLIC METHODS
//

// Constructor
Player::Player(int boardSize)
{
    board = Board(boardSize);
    unassignedShips = {AircraftCarrier, Battleship, Cruiser, Destroyer, UBoat};
}

// Record the result of a shit
// True indicates a hit, false a miss
void Player::fireShot(Cell target, Player &opponent)
{
    if (opponent.receiveShot(target))
    {
        // Hit
        std::cout << "It's a hit!" << std::endl;
        hits.push_back(target);
    }
    else
    {
        // Miss
        std::cout << "It's a miss." << std::endl;
        misses.push_back(target);
    }
}

// Get all recorded hits and misses
std::vector<Cell> Player::getAllShots() const
{
    return board.getAllShots();
}

// Getter for the board -- TODO should the caller just use const_cast?
Board Player::getBoard()
{
    return board;
}

// Const Getter for the board
Board Player::getBoardConst() const
{
    return board;
}

// Return the board output as a vector of strings, one per line
// TODO make COmputer more able to reuse this somehow
lines Player::toLineStrings(GameState gs) const
{
    // add "Player"  - or "Computer" -  header
    lines ret = {};

    ret.push_back("                Player           ");
    ret.push_back("Ships alive:                        ");
    std::string base = remainingShipsStr(gs);
    base.append("                     ");
    ret.push_back(base);
    ret.push_back("");
    // insert board line strings
    lines boardLines = board.toLineStrings(true);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}

// Receive a shot
bool Player::receiveShot(Cell target)
{
    return board.receiveShot(target);
}

// Run the placement loop to prompt user for ship locations
void Player::runPlacement()
{
    // <iostream>
    using std::cin;
    using std::cout;
    using std::endl;

    // <string>
    using std::string;

// Continually prompt to place ships until there are none left
outer:
    while (unassignedShips.size() > 0)
    {
        // display board
        cout << toLineStrings(GameState::Placement);

        // Prompt user for which ship to place
        ShipClass shipChoice = getShipClass();
        // catch for runRandom
        if (shipChoice == 'R')
        {
            // place the rest of the ships randomly
            randomlyPlaceShips();
            // skip to next iteration of loop, which should now fail the check
            continue;
        }
        cout << "Placing " << shipChoice << "." << endl;

        // Prompt user for origin
        Cell origin = getOrigin(shipChoice);
        cout << origin << endl;

        // get direction - default to Left arbitrarily
        Direction d = Direction::Left;

        // Check if the ship fits either way
        // If it fits one way or the other, set the direction automatically
        // If both work, prompt to choose
        bool fitsLeft = board.doesFit(ShipPlacement(origin, Direction::Left, shipChoice));
        bool fitsDown = board.doesFit(ShipPlacement(origin, Direction::Down, shipChoice));
        if (!fitsLeft && !fitsDown)
        {
            // Can't possibly place with that origin
            // Tell them it's gonna be left or down, try again
            cout << "Cannot place " << shipChoice << " at that location." << endl
                 << "You will orient Left or Down from the origin.  Please pick a new origin." << endl;
            continue;
        }
        else if (fitsLeft && !fitsDown)
        {
            // must be Left - inform the user
            cout << shipChoice << " only fits left.  Saving..." << endl;
            // technically no need to set, it should be Left already, but just in case
            d = Direction::Left;
        }
        else if (!fitsLeft && fitsDown)
        {
            // must be Down - inform the user
            cout << shipChoice << " only fits down.  Saving..." << endl;
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

        // Confirm triple

        char confirmChoice = 'x';
        bool startOver = false;
        for (;;)
        {
            //TODO first, show the board with the ship placed - a Board::removeShip method would be good
            // not urgent

            // display all three choices
            cout << "Origin: " << origin << endl
                 << "Class: " << shipChoice << " (Length: " << shipChoice.size() << ")" << endl
                 << "Direction: " << d << endl
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
        placeShip(ShipPlacement(origin, d, shipChoice));
    }
}
