#include "game.h"

Game::Game()
{
    player = Player();
}

std::string Game::toString()
{
        return "Game!\n" + player.toString();
};