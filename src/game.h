#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>

#include "player.h"
#include "display.h"

class Game
{
private:
    // the two players.
    std::vector<std::unique_ptr<Player>> players;
    int turn; // current turn. this can only be 0 or 1.
    Display display;

public:
    void endTurn();
    void shuffle(Player);
};

#endif
