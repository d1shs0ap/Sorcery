#include "game.h"

using namespace std;

// Constructor
Game::Game(shared_ptr<Player> player1, shared_ptr<Player> player2, unsigned seed)
    : seed {seed} {
    players.push_back(player1);
    players.push_back(player2);

    // Generate randomly which player starts first
    mt19937_64 generator (seed);
    uniform_int_distribution<int> distribution(0, 1);
    activePlayer = distribution(generator);
}
// Does all the start turn game effects
void startTurn();
// Does all the end turn game effects
void endTurn();
// Checks all triggered abilities to see if any is triggered
void checkTriggered();
// Steps the game after each player action
void step();
Player *getPlayer(int index);
