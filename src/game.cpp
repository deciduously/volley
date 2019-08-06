#include <algorithm>
#include <iostream>

#include "game.h"

//
// PRIVATE METHODS
//

// Return a vector of strings containing both boards side by side
lines Game::bothBoardLines() const
{
    // Init return value to player board output lines
    lines ret = player->toLineStrings();

    // The computer board output lines
    lines computerLines = computer->toLineStrings();

    // Grab size
    int boardSize = computerLines.size();

    // Each line, mash together the player and computer board side by side
    for (int i = 0; i < boardSize; i++)
    {
        ret[i].append("         "); // 10 spaces
        ret[i].append(computerLines[i]);
    }
    return ret;
}

// Pick a random target avoiding a specific board's recorded hits and misses
Cell Game::getRandomTarget(const Player &opponent) const
{
    return opponent.getBoardConst()->getRandomTarget();
}

// Prompt the user for a target
Cell Game::promptTarget() const
{
    // TODO this will have to change if we support hotseat
    return computer->getBoardConst()->promptCell("Target");
}

// Reset a completed game to play again
void Game::resetGame()
{
    delete player;
    delete computer;
    player = new Player();
    computer = new Computer();
    gameState = GameState::Firing;
}

// Run the fire loop until someone wins
bool Game::runFiring()
{
    using std::cin;
    using std::cout;
    using std::endl;

    cout << endl
         << "Guns at the ready!" << endl
         << endl;
    while (gameState == GameState::Firing)
    {
        // Run turns until someone wins - TODO refactor
        // Board::getRandomTarget? - that builds in the avoiding check

        // Display both boards
        cout << bothBoardLines() << endl;

        // run player turn

        // Get a target that hasn't been fired at
        Cell nextTarget = promptTarget();
        cout << nextTarget.toString() << endl;

        // Fire the shot at the computer, store the result in the player
        // fireShot returns a boolean, used in the computer's seeking function - unused here
        player->fireShot(nextTarget, *computer);

        // check if you won
        if (computer->remainingShipsCount() == 0)
        {
            gameState = GameState::GameOver;
            char playAgain;
            cout << "You have won the game!  Congratulations.  Play again? (Y/N)> ";
            cin >> playAgain;

            if (toupper(playAgain) == 'Y')
                return true;
            else
                return false;
        }

        // run computer turn
        computer->executeFire(*player);

        // check if the computer just won
        if (player->remainingShipsCount() == 0)
        {
            gameState = GameState::GameOver;
            char playAgain;
            cout << "The computer has won the game.  You should be ashamed.  Play again? (Y/N)> ";
            cin >> playAgain;

            if (toupper(playAgain) == 'Y')
                return true;
            else
                return false;
        }
    }
    // This is unreachable - someone will always win
    return true;
}

// Run ship placement for both players
void Game::runPlacement()
{
    std::cout << std::endl
              << "Stage your battlefield!" << std::endl
              << std::endl;
    player->runPlacement();
    computer->runPlacement();
}

//
// PUBLIC METHODS
//

// Constructor
Game::Game()
{
    player = new Player();
    computer = new Computer();
    gameState = GameState::Placement;
}

// Constructor specifying board size
Game::Game(int boardSize)
{
    player = new Player(boardSize);
    computer = new Computer(boardSize);
    gameState = GameState::Placement;
}

// Destructor
Game::~Game()
{
    delete player;
    delete computer;
}

// Run the game
void Game::run()
{
    bool playAgain = true;

    while (playAgain)
    {
        runPlacement();
        gameState = GameState::Firing;
        playAgain = runFiring();

        // cleanup if needed
        if (playAgain)
            resetGame();
    }
    std::cout << "Game over!" << std::endl;
}

// Getter for board size
int Game::size() const
{
    return player->getBoardConst()->size();
}