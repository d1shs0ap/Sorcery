#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <random>
#include <chrono>

#include "player.h"
#include "../cards/minion/triggeredAbility.h"

class Deck;

class Game : public std::enable_shared_from_this<Game> {
    // the two players.
    std::vector<std::shared_ptr<Player>> players;
    int activePlayer; // current turn. this can only be 0 or 1.
    unsigned seed; // to generate the first active player

    public:
        // Constructor
        Game(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, unsigned seed);
        // Removes everything that is no longer on the board
        void clean();
        // Does all the start turn game effects
        void startTurn();
        // Does all the end turn game effects
        void endTurn();
        // Checks all triggered abilities to see if any is triggered, under a certain situation
        void checkTriggered(int context);
        // Changes active player
        void changeActive();
        // Get the winner, if there is one
        int getWinner();

        std::shared_ptr<Player> getActivePlayer();
        std::shared_ptr<Player> getInactivePlayer();
        std::shared_ptr<Player> getPlayer(int index);
};

#endif
