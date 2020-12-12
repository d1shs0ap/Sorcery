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

// Removes everything that is no longer on the board
void Game::clean() {
    
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
    checkTriggered(START_TURN);
}

// Does all the end turn game effects
void Game::endTurn() {
    // Check all triggered abilities (minions and ritual)
    checkTriggered(END_TURN);
}

// Checks all triggered abilities to see if any is triggered, in a certain context(e.g. endTurn)
void Game::checkTriggered(int context) {
    // player and its components
    auto player = getActivePlayer();
    auto board = player->getBoard();
    auto ritualTrgAbility = board->getRitual()->getTrgAbility();

    // enemy player and its components
    auto enemyPlayer = getInactivePlayer();
    auto enemyBoard = enemyPlayer->getBoard();
    auto enemyRitualTrgAbility = enemyBoard->getRitual()->getTrgAbility();

    if (context==START_TURN || context==END_TURN) {
        // check the active player's ritual and minions for triggered abilities
        if (ritualTrgAbility.getType()==context) {
            ritualTrgAbility.effect(*this);
        }
        for(auto minion : board->getMinions()) {
            auto trgAbility = minion->getTrgAbility();
            if (trgAbility.getType()==context) {
                trgAbility.effect(*this);
            }
        }
        
        // check the enemy player's ritual and minions for triggered abilities
        if (enemyRitualTrgAbility.getType()==context) {
            enemyRitualTrgAbility.effect(*this);
        }
        for(auto minion : enemyBoard->getMinions()) {
            auto trgAbility = minion->getTrgAbility();
            if (trgAbility.getType()==context) {
                trgAbility.effect(*this);
            }
        }
    } else if (context == MINION_ENTER) { // when the active player's a minion
        // for active player's minions, we also have to check that if its triggered ability is of type "OWN_MINION_ENTER"
        if (ritualTrgAbility.getType()==MINION_ENTER || ritualTrgAbility.getType()==OWN_MINION_ENTER) {
            ritualTrgAbility.effect(*this);
        }
        for(auto minion : board->getMinions()) {
            auto trgAbility = minion->getTrgAbility();
            if (trgAbility.getType()==MINION_ENTER || trgAbility.getType()==OWN_MINION_ENTER) {
                trgAbility.effect(*this);
            }
        }

        // for enemy's minions, we also have to check that if its triggered ability is of type "ENEMY_MINION_ENTER"
        if (enemyRitualTrgAbility.getType()==MINION_ENTER || enemyRitualTrgAbility.getType()==ENEMY_MINION_ENTER) {
            enemyRitualTrgAbility.effect(*this);
        }
        for(auto minion : enemyBoard->getMinions()) {
            auto trgAbility = minion->getTrgAbility();
            if (trgAbility.getType()==MINION_ENTER || trgAbility.getType()==ENEMY_MINION_ENTER) {
                trgAbility.effect(*this);
            }
        }

    }

    // auto enemyPlayer = getInactivePlayer();
}

// Changes active player
void Game::changeActive() {
    activePlayer = 1 - activePlayer;
}

// Get the winner, if there is one
int Game::getWinner() {
    auto player1 = getPlayer(0);
    auto player2 = getPlayer(1);
    if(player1->getLife() <= 0 && player2->getLife() <= 0 ) {
        return 0;
    } else if (player1->getLife() <= 0) {
        return 2;
    } else if (player2->getLife() <= 0) {
        return 1;
    }
    return -1;
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

// get player by index
shared_ptr<Player> Game::getPlayer(int index) {
    return players[index];
}
