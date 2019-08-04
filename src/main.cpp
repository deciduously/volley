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
    Game *game = new Game();

    // Display header
    int headerWidth = 25;
    cout << endl
         << setw(headerWidth) << right << "Battleship!!!" << endl
         << endl;

    // run game loop
    game->run();

    // clean up game
    delete game;

    // quit the process, which does all the proper stdlib cleanup
    std::exit(0);

    // Return success - unnecessary?  std::exit(0) is where execution completes
    return 0;
}