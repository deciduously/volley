#include <iostream>
#include <string>
#include <tuple>
#include <vector>

enum Direction {Left, Right};
enum GameState {Firing, GameOver, Placement};
enum ShipClass {AircraftCarrier = 5, Battleship = 4, Cruiser = 3, Destroyer = 2, UBoat = 3};

class Ship
{
    std::tuple<int, int> origin;
    Direction direction;
    int hits;
    ShipClass shipClass;
    public:
        Ship(int row, int col, Direction dir, ShipClass sc)
        {
            origin = std::make_tuple(row, col);
            direction = dir;
            shipClass = sc;
            hits = shipClass;
        };
};

class Board
{
    std::vector<Ship> ships;
    public:
        std::string toString()
        {
            return "Board!";
        }
};

class Player
{
    Board board;
    std::vector<ShipClass> unassignedShips;
    public:
        Player()
        {
            unassignedShips = {AircraftCarrier, Battleship, Cruiser, Destroyer, UBoat};
        };
        std::string toString()
        {
            return "Player";
        }
};

class Computer : public Player
{
    std::vector<std::tuple<int, int>> neighborhood;
    public:
        Computer()
        {
            neighborhood = {};
        };
};

class Game
{
    Player player;
    public:
        std::string toString()
        {
            return "Game!";
        };
};

int main()
{
    std::cout << "Battleship" << std::endl;
    Game game = Game();
    std::cout << game.toString() << std::endl;

    return 0;
}