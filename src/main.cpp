/* 
* main.cpp
* Entrypoint for the Battleship game
* Benjamin Lovy
*/
#include <iostream>

#include "game.h"

int main()
{
    std::cout << "               Battleship!!!" << std::endl << std::endl;
    Game game = Game();
    game.run();

    return 0;
}