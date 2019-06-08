#include <iostream>

#include "game.h"

int main()
{
    std::cout << "Battleship" << std::endl;
    Game game = Game();
    std::cout << game.toString() << std::endl;

    return 0;
}