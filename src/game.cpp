#include <iostream>

#include "game.h"

//
// PRIVATE METHODS
//

// Run the fire loop until someone wins
void Game::runFiring()
{
    using std::cout;
    using std::endl;

    cout << toStringFiring() << endl;
}

// Run the placement loop until all unplaced ships are placed
void Game::runPlacement()
{
    std::cout << std::endl
              << "Stage your battlefield!" << std::endl
              << std::endl;
    player.runPlacement();
    computer.runPlacement();
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

//
// PUBLIC METHODS
//

Game::Game(int boardSize)
{
    player = Player(boardSize);
    computer = Computer(boardSize);
    gameState = GameState::Placement;
}

// Run the game
void Game::run()
{
    runPlacement();
    std::cout << std::endl
              << "Guns at the ready!" << std::endl
              << std::endl;
    gameState = GameState::Firing;
    runFiring();
}