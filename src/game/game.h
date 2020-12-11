#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <random>
#include <chrono>

#include "subject.h"
#include "player.h"

class Game : Subject{
    // the two players.
    std::vector<std::shared_ptr<Player>> players;
    int activePlayer; // current turn. this can only be 0 or 1.
    unsigned seed; // to generate the first active player

    public:
        // Constructor
        Game(shared_ptr<Player> player1, shared_ptr<Player> player2, unsigned seed);
        // Does all the start turn game effects
        void startTurn();
        // Does all the end turn game effects
        void endTurn();
        // Checks all triggered abilities to see if any is triggered
        void checkTriggered();
        // Steps the game after each player action
        void step();
        Player *getPlayer(int index);
};

#endif
