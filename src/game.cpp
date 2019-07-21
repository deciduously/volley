#include "game.h"

Game::Game()
{
    player = Player();
}

std::string Game::toString()
{
    // The return string
    std::string ret = "";

    // The player board output lines
    std::vector<std::string> playerLines = player.toLineStrings();

    // The computer board output lines
    std::vector<std::string> computerLines = computer.toLineStrings();

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
        ret.append("\n");
    }
    return ret;
}