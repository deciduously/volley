#include "player.h"

Player::Player()
{
    unassignedShips = {AircraftCarrier, Battleship, Cruiser, Destroyer, UBoat};
}
std::vector<std::string> Player::toLineStrings()
{
    return board.toLineStrings();
}