/* 
* util.h
* Various enums and functions that don't belong to a particular class
* Benjamin Lovy
*/
#ifndef __UTIL_H_INCLUDED
#define __UTIL_H_INCLUDED

#include <string>
#include <vector>

// Helper function to clear out cin to loop for input again
void clearCin();

// Board size is fixed
const int BOARD_SIZE = 10;

// A Ship can be either horizontal or vertical
// The occupied cells are extrapolated from an origin and a Direction
enum class Direction
{
    Right,
    Down
};

// ostream overload for Direction
std::ostream &operator<<(std::ostream &stream, const Direction &d);

// The three possible gamestates
enum class GameState
{
    Firing,
    GameOver,
    Placement
};

// string vector alias
typedef std::vector<std::string> lines;

// ostream overload for lines
std::ostream &operator<<(std::ostream &stream, const lines &l);

// A single cell on the board
typedef struct Cell
{
    int row = 1;
    char col = 'A';
    // Default constructor
    Cell();
    //Constructor from two ints
    Cell(int r, int c);
    // Constructor from an int and a col
    Cell(int r, char c);
    // == overload
    bool operator==(const Cell &other) const;
    std::string toString() const;
} Cell;

// Stream overload
std::ostream &operator<<(std::ostream &stream, const Cell &c);

// ShipClass

// Each possible type, or Unknown for error or hit detection
enum class ShipClassType
{
    AircraftCarrier,
    Battleship,
    Cruiser,
    Destroyer,
    UBoat,
    Unknown
};

// Struct for ergonomic ShipClassType getters
typedef struct ShipClass
{
    ShipClassType sct = ShipClassType::Unknown;
    // Constructors
    // Default constructor
    ShipClass();
    // Construct a ShipClass from a char
    ShipClass(char c);
    // Construct a ShipClass from ShipClassType
    ShipClass(ShipClassType sc);

    // Overload
    bool operator==(const ShipClass &other) const;

    // Getters
    // Get the corresponding length for each ShipClass variant
    int size() const;
    // Get the corresponding char for each ShipClass variant
    char toChar() const;
    // Pretty-print the ShipClass enum in long-form text
    std::string toString() const;
    // Getter for ShipClassType
    ShipClassType type() const;
} ShipClass;

// Stream overload
std::ostream &operator<<(std::ostream &stream, const ShipClass &sc);

#endif