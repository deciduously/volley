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
    using std::cout;
    using std::endl;
    using std::setw;
    using std::right;
    
    cout << endl << setw(20) << right << "Battleship!!!" << endl << endl;
    Game game = Game();
    game.run();

    return 0;
}