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
    using std::setw;
    using std::right;

    // Instantiate game object
    Game game = Game();
    
    // Output header
    // We want it halfway across the board
    // Each board column is 3 spaces, and there's an inital one for the labels
    int headerWidth = (game.getSize() * 3 + 3) / 2;
    cout << endl << setw(20) << right << "Battleship!!!" << endl << endl;
    
    // run game loop
    game.run();

    return 0;
}