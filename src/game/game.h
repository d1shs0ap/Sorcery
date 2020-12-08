#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "subject.h"
#include "player.h"

class Game : Subject{
    // the two players.
    std::vector<std::unique_ptr<Player>> players;
    int activePlayer; // current turn. this can only be 0 or 1.

    public:
        // Does all the start turn game effects
        void startTurn();
        // Does all the end turn game effects
        void endTurn();
        // Checks all triggered abilities to see if any is triggered
        void checkTriggered();
        // Steps the game after each player action
        void step();
};

#endif