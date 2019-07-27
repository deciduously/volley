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
    while (gameState == GameState::Firing)
    {
        // Run turns until someone wins

        // Display both boards
        cout << toStringFiring() << endl;

        // Get a target that hasn't been fired at
        std::vector<Cell> toAvoid = computer.getBoard().getAllShots();
        Cell nextTarget = Cell();
        do
        {
            nextTarget = promptTarget();
        } while (std::find(toAvoid.begin(), toAvoid.end(), nextTarget) != toAvoid.end());

        cout << nextTarget.toString() << endl;

        // artificially end the game - TODO REMOVE
        gameState = GameState::GameOver;
    }
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
    std::cout << "Game over!" << std::endl;
}

// Getter for board size
int Game::size()
{
    return player.getBoard().size();
}