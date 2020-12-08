#ifndef VIEW_H
#define VIEW_H

#include <vector>

#include "observer.h"
#include "../game/game.h"

class View : public Observer {
    Game game;
    std::vector<std::vector<char>> display;
    public:
        void display();
};

#endif
