#include "game.h"

Game::Game()
{
    player = Player();
    computer = Computer();
    gameState = GameState::Placement;
}

std::string Game::toStringFiring()
{
    // The return string
    std::string ret = "";

    // The player board output lines
    lines playerLines = player.toLineStrings();

    // The computer board output lines
    lines computerLines = computer.toLineStrings();

    // THis should be the same for both, so grab either
    int playerLinesSize = playerLines.size();

    // Each line, mash together the player and computer board side by side
    for (int i = 0; i < playerLinesSize; i++)
    {
        std::string rowString = "";
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