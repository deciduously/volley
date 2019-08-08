/*
* player.cpp
* Represents a player of a game of Battleship
* Contains their respective Board
* Benjamin Lovy
*/
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
    Board *b = getBoardConst();

    // Ensure what they pick fits at least one way
    do
    {
        ret = board->promptCell("Origin");
        if (ret == Cell(b->size() + 1, b->size() + 1))
        {
            ret = b->getRandomCell();
        }
    } while (!board->doesFit(ShipPlacement(ret, Direction::Right, sc)) && !board->doesFit(ShipPlacement(ret, Direction::Down, sc)));

    return ret;
}

// Return a random direction for the given origin and shipclass that fit - it's already ensured at least one of the two does
Direction Player::getRandomDirection(Cell origin, ShipClass sc) const
{
    bool fitsRight = getBoardConst()->doesFit(ShipPlacement(origin, Direction::Right, sc));
    bool fitsDown = board->doesFit(ShipPlacement(origin, Direction::Down, sc));
    // don't bother doing the check for if neither work, getRandomOrigin checked it until one or the other did
    if (fitsRight && !fitsDown)
    {
        return Direction::Right;
    }
    else if (!fitsRight && fitsDown)
    {
        return Direction::Down;
    }
    else
    {
        // it fits both ways, choose one randomly
        int dirChoice = rand() % 2;
        if (dirChoice == 1)
        {
            return Direction::Right;
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
        ret = board->getRandomCell();
        // move on if it fits either way - placement will handle choosing a direction
    } while (!board->doesFit(ShipPlacement(ret, Direction::Right, sc)) && !board->doesFit(ShipPlacement(ret, Direction::Down, sc)));

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
        // if there's only one Right, autoselect it
        if (unassignedShips.size() == 1)
        {
            cout << "One ship Right: placing " << unassignedShips[0].toString() << endl;
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
        for (size_t i = 0; i < unassignedShips.size(); i++)
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
    board->pushShip(Ship(sp));
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
    int shipsLeft = unassignedShips.size();
    for (int i = 0; i < shipsLeft; i++)
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
        toShow = getBoardConst()->remainingShips();
        break;
    case GameState::GameOver:
        std::cerr << "Something weird and unexpected has happened" << std::endl;
        std::exit(1);
        break;
    }

    // Open string with a bracket
    string ret = "{ ";

    // Iterate through the unassigned ships, adding them to the output
    for (size_t i = 0; i < toShow.size(); i++)
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

// Default Constructor
Player::Player()
{
    board = new Board(BOARD_SIZE);
    name = "The Player";
    unassignedShips = ALL_SHIP_CLASSES;
}

// Constructor
Player::Player(int boardSize, std::string n)
{
    board = new Board(boardSize);
    name = n;
    unassignedShips = ALL_SHIP_CLASSES;
}

// Destructor
Player::~Player()
{
    delete board;
}

// Record the result of a shit
// True indicates a hit, false a miss
bool Player::fireShot(Cell target, Player &opponent)
{
    // get the number of ships opponent has left
    int shipsLeftBefore = opponent.remainingShipsCount();
    // fire the shot
    ShipClass result = opponent.receiveShot(target);
    if (result.type() != ShipClassType::Unknown)
    {
        // Hit - record it, check for a sunk ship
        std::cout << "It's a hit!" << std::endl;
        hits.push_back(target);
        // check if it sank
        if (opponent.remainingShipsCount() < shipsLeftBefore)
        {
            std::cout << getName() << " sank " << opponent.getName() << "'s " << result << "!" << std::endl;
        }
        return true;
    }
    else
    {
        // Miss - nothing to record
        std::cout << "It's a miss." << std::endl;
        return false;
    }
}

// Getter for the board -- TODO should the caller just use const_cast?
Board *Player::getBoard()
{
    return board;
}

// Const Getter for the board
Board *Player::getBoardConst() const
{
    return board;
}

// Getter for name
std::string Player::getName() const
{
    return name;
}

// Receive a shot
ShipClass Player::receiveShot(const Cell target)
{
    return board->receiveShot(target);
}

// Returns the number of ships with a positive number of hits
int Player::remainingShipsCount() const
{
    return board->remainingShipsCount();
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

// Continually prompt to place ships until there are none Right
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

        // get direction - default to Right arbitrarily
        Direction d = Direction::Right;

        // Check if the ship fits either way
        // If it fits one way or the other, set the direction automatically
        // If both work, prompt to choose
        bool fitsRight = board->doesFit(ShipPlacement(origin, Direction::Right, shipChoice));
        bool fitsDown = board->doesFit(ShipPlacement(origin, Direction::Down, shipChoice));
        if (!fitsRight && !fitsDown)
        {
            // Can't possibly place with that origin
            // Tell them it's gonna be Right or down, try again
            cout << "Cannot place " << shipChoice << " at that location." << endl
                 << "You will orient Right or Down from the origin.  Please pick a new origin." << endl;
            continue;
        }
        else if (fitsRight && !fitsDown)
        {
            // must be Right - inform the user
            cout << shipChoice << " only fits Right.  Saving..." << endl;
            // technically no need to set, it should be Right already, but just in case
            d = Direction::Right;
        }
        else if (!fitsRight && fitsDown)
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
                cout << "(R)ight or (D)own> ";
                cin >> directionChoice;
                directionChoice = toupper(directionChoice);
                if (directionChoice == 'R' || directionChoice == 'D')
                {
                    if (directionChoice == 'R')
                    {
                        d = Direction::Right;
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
                    cout << "Please enter \"R\" or \"D\"." << endl;
                    continue;
                }
            }
        }

        // Confirm triple

        char confirmChoice = 'x';
        for (;;)
        {
            //  Place the given triple
            placeShip(ShipPlacement(origin, d, shipChoice));
            cout << "PREVIEW:" << endl
                 << endl
                 << toLineStrings() << endl;

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
                // remove ship and add it back to the options
                board->removeShip(shipChoice);
                unassignedShips.push_back(shipChoice);
                // jump back to the very top
                goto outer;
            }
            else
            {
                cout << "Confirmed!  Saving ship location..." << endl;
                break;
            }
        }
    }
}

// Return the board output as a vector of strings, one per line
lines Player::toLineStrings(GameState gs) const
{
    // add "Player"  - or "Computer" -  header
    lines ret = {};

    ret.push_back("                Player           ");
    if (gs == GameState::Firing)
    {
        ret.push_back("Ships alive:                        ");
        std::string base = remainingShipsStr(gs);

        // first, add the base padding - 21 spaces
        base.append("                    ");
        // then add 4 spaces for each sunk ship
        int sunkShips = ALL_SHIP_CLASSES.size() - remainingShipsCount();
        for (int i = 0; i < sunkShips; i++)
        {
            base.append("    ");
        }

        ret.push_back(base);
        ret.push_back("");
    }
    // insert board line strings
    lines boardLines = getBoardConst()->toLineStrings(true);
    ret.insert(ret.end(), boardLines.begin(), boardLines.end());
    return ret;
}