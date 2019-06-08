#ifndef __GAME_H_INCLUDED
#define __GAME_H_INCLUDED

#include "player.h"

class Game
{
    Player player;
    public:
        Game();
        std::string toString();
};
#endif