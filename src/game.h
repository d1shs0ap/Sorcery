#ifndef GAME_H`
#define GAME_H

#include <vector>

#include "player.h"

class Game {
  public:
    // Keeps track of players
    vector<unique_ptr<Player>>
    // Keeps track of whose turn it is currently
    int curPlayer;

    void endTurn();

    void shuffle(Player player);
};

#endif
