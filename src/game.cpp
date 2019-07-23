#include "game.h"

Game::Game()
{
    int size = getSize();
    player = Player(size);
    computer = Computer(size);
    gameState = GameState::Placement;
}

std::string Game::toStringFiring()
{
    using std::string;
    // The return string
    string ret = "";

    // The player board output lines
    lines playerLines = player.toLineStrings();

    // The computer board output lines
    lines computerLines = computer.toLineStrings();

    // THis should be the same for both, so grab either
    int playerLinesSize = playerLines.size();

    // Each line, mash together the player and computer board side by side
    for (int i = 0; i < playerLinesSize; i++)
    {
        string rowString = "";
        rowString.append(playerLines[i]);
        rowString.append("          ");
        rowString.append(computerLines[i]);
        ret.append(rowString);
        ret.push_back('\n');
    }
    return ret;
}

// Run the fire loop until someone wins
void Game::runFiring()
{

}

// Run the placement loop until all unplaced ships are placed
void Game::runPlacement()
{
    player.runPlacement();
    //computer.runPlacement(); // this will be automated
}

// PUBLIC

// Run the game
void Game::run()
{
    runPlacement();
    gameState = GameState::Firing;
    runFiring();
}

// Getter for the board size - currently hardcoded to 10 in player.cpp
int Game::getSize()
{
    return size;
}