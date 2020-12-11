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
void Game::startTurn() {
    // change active player
    changeActive();
    // gain magic
    auto player = getActivePlayer();
    player->setMagic(player->getMagic() + 1);
    // draw card
    player->draw();
    // Check all triggered abilities (minions and ritual)
    checkTriggered();
}
// Does all the end turn game effects
void Game::endTurn() {
    // Check all triggered abilities (minions and ritual)
    checkTriggered();
}
// Checks all triggered abilities to see if any is triggered
void Game::checkTriggered() {

}

// Changes active player
void Game::changeActive() {
    activePlayer = 1 - activePlayer;
}

// get the active player
shared_ptr<Player> Game::getActivePlayer() {
    return players[activePlayer];
}
// get the inactive player
shared_ptr<Player> Game::getInactivePlayer() {
    if(activePlayer==0){
        return players[1];
    }
    return players[0];
}
