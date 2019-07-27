#include <algorithm>
#include <iostream>

#include "game.h"

//
// PRIVATE METHODS
//

// Pick a random target avoiding a specific board's recorded hits and misses
Cell Game::getRandomTarget(Player opponent)
{
    Cell ret = Cell();
    std::vector<Cell> cellsToAvoid = opponent.getAllShots();
    do
    {
        ret = opponent.getBoard().getRandomCell();
        // Check if the opponent's board contains this cell
    } while (std::find(cellsToAvoid.begin(), cellsToAvoid.end(), ret) != cellsToAvoid.end());

    return ret;
}

// Prompt the user for a target
Cell Game::promptTarget()
{
    Board b = player.getBoard();
    Cell ret = b.promptCell("Target");
    if (ret == Cell())
    {
        ret = b.getRandomCell();
        std::cout << "Randomly selecting: " << ret.toString() << std::endl
                  << std::endl;
    }
    return ret;
}

// Run the fire loop until someone wins
void Game::runFiring()
{
    using std::cout;
    using std::endl;

    cout << endl
         << "Guns at the ready!" << endl
         << endl;
    cout << toStringFiring() << endl;
}

// Run ship placement for both players
void Game::runPlacement()
{
    std::cout << std::endl
              << "Stage your battlefield!" << std::endl
              << std::endl;
    player.runPlacement();
    computer.runPlacement();
}

// Render the game string with both players side-by-side during the Firing stage
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
    gameState = GameState::Firing;
    runFiring();
}

// Getter for board size
int Game::size()
{
    return player.getBoard().size();
}