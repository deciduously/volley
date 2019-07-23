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

    // Instantiate game object
    Game game = Game(BOARD_SIZE);

    // Output header
    // We want it halfway across the board
    // Each board column is 3 spaces, and there's an inital one for the labels
    // (10 * 3 + 3) / 2-ish
    int headerWidth = 16;
    cout << endl
         << setw(headerWidth) << right << "Battleship!!!" << endl
         << endl;

    // run game loop
    game.run();

    return 0;
}