/* 
* main.cpp
* Entrypoint for the Battleship game
* Benjamin Lovy
*/
#include <iomanip>
#include <iostream>

#include "game.h"

int main()
{
    // <iostream>
    using std::cout;
    using std::endl;

    // <iomanip>
    using std::right;
    using std::setw;

    // Init random seed
    srand(time(0));

    // Instantiate game object
    Game *game = new Game(BOARD_SIZE);

    // Display header
    int headerWidth = 25;
    cout << endl
         << setw(headerWidth) << right << "Battleship!!!" << endl
         << endl;

    // run game loop
    game->run();

    // Cleanup
    delete game;

    // quit the process, which does all the proper stdlib cleanup
    std::exit(0);

    // Return success (?)
    return 0;
}