#include "player.h"

Player::Player()
{
    unassignedShips = {AircraftCarrier, Battleship, Cruiser, Destroyer, UBoat};
}
std::string Player::toString()
{
    return "Player\n" + board.toString();
}