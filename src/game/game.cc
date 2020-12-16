#include "game.h"
#include "player.h"
#include "../cardCollections/board.h"
#include "../cardCollections/graveyard.h"
#include "../cards/minion/triggeredAbility.h"
#include "../cards/ritual.h"
#include "../cards/minion/minion.h"
#include "../cards/minion/enchantment.h"
#include "../argException.h"



using namespace std;

// Constructor
Game::Game(shared_ptr<Player> player1, shared_ptr<Player> player2, mt19937_64& generator)
    : generator {generator} {
    players.push_back(player1);
    players.push_back(player2);

    // Generate randomly which player starts first
    uniform_int_distribution<int> distribution(0, 1);
    activePlayer = distribution(generator);
}

// Removes everything that is no longer on the board
void Game::clean() {
    for (auto player : players){
        auto minions = player->getBoard()->getMinions();
        std::vector<shared_ptr<Minion>> deadMinions;
        for(int i = 0; i < minions.size(); ++i) {
            std::shared_ptr<Minion> target = player->getBoard()->getMinion(i);
            if (target->getDef() <= 0){
                deadMinions.push_back(target);
            }
        }
        for(auto toBeRemoved : deadMinions){
            int index = player->getBoard()->findMinion(toBeRemoved);
            if(index >= 0){ destroyMinion(player, index); }
        }
    }
}

// Does all the start turn game effects
void Game::startTurn() {
    // change active player
    changeActive();
    // gain magic
    auto player = getActivePlayer();
    player->setMagic(player->getMagic() + 1);
    // restore actionp oints
    player->getBoard()->restoreActionAll();
    // draw card
    player->draw();
    // Check all triggered abilities (minions and ritual)
    checkTriggered(getActivePlayer(), TriggeredAbilityType::START_TURN);
}

// Does all the end turn game effects
void Game::endTurn() {
    // Check all triggered abilities (minions and ritual)
    checkTriggered(getActivePlayer(), END_TURN);
    auto player = getActivePlayer();
    auto board = player->getBoard();
    for(int i = 0; i < board->getMinions().size(); i++){
        std::shared_ptr<Minion> minion = board->getMinion(i);
        if(minion->getName().compare("Delay") == 0){
            std::shared_ptr<Delay> delay = std::static_pointer_cast<Delay>(minion);
            if(delay->getRound() == 1){
                getActivePlayer()->getBoard()->setMinion(i, delay->detach());

            }
        }
    }
}

// Checks all triggered abilities to see if any is triggered, in a certain context(e.g. endTurn)
void Game::checkTriggered(std::shared_ptr<Player> player, int context) {
    // player and its components
    auto board = player->getBoard();
    auto ritual = board->getRitual();
    
    std::shared_ptr<Player> enemyPlayer;
    if(getActivePlayer() == player) {
        enemyPlayer = getInactivePlayer();
    } else{
        enemyPlayer = getActivePlayer();
    }
    auto enemyBoard = enemyPlayer->getBoard();
    auto enemyRitual = enemyBoard->getRitual();

    if (context==START_TURN || context==END_TURN) {
        // check there is ritual
        if (ritual != nullptr) {
            auto ritualTrgAbility = ritual->getTrgAbility();
            
            // check there is trg ability of ritual
            if(ritualTrgAbility != nullptr){
                
                if(ritualTrgAbility->getType()==context) {
                    bool triggered = ritual->useTrgAbility(shared_from_this());
                    if (!triggered) {
                        // print message saying that ritual do not have enough charges to continue
                        throw ArgException{"Ritual " + ritual->getName() + " does not have enough charges to be triggered."};
                    }
                }
            } else {
                // error because all rituals have trg abilities
                throw ArgException{"Ritual " + ritual->getName() + " does not have triggered ability."};
            }
        }

        for(auto minion : board->getMinions()) {
            // checks if minion has trg ability
            if(minion->hasTrgAbility()) {
                
                auto trgAbility = minion->getTrgAbility();
                if (trgAbility->getType()==context) {
                    
                    //Use minion to call
                    trgAbility->effect(shared_from_this(), minion);
                }
            }
        }
    } else if (context == MINION_ENTER) { // when the active player's a minion
        // for active player's minions, we also have to check that if its triggered ability is of type "OWN_MINION_ENTER"
        // check there is ritual
        if (ritual != nullptr) {
            auto ritualTrgAbility = ritual->getTrgAbility();

            // check if ritual has trg ability
            if(ritualTrgAbility != nullptr){
                if (ritualTrgAbility->getType()==MINION_ENTER || ritualTrgAbility->getType()==OWN_MINION_ENTER) {
                    bool triggered = ritual->useTrgAbility(shared_from_this());
                    if (!triggered) {
                        // print message saying that ritual do not have enoguh charges to continue
                        throw ArgException{"Ritual " + ritual->getName() + " does not have enough charges to be triggered."};
                    }
                }
            } else {
                // if ritual has no trg ability, error
                throw ArgException{"Ritual " + ritual->getName() + " does not have triggered ability."};
            }
        }

        for(auto minion : board->getMinions()) {
            // checks if minion has trg ability
            if(minion->hasTrgAbility()) {
                auto trgAbility = minion->getTrgAbility();
                if (trgAbility->getType()==MINION_ENTER || trgAbility->getType()==OWN_MINION_ENTER) {

                    trgAbility->effect(shared_from_this(), minion);
                }
            }
        }


        // for enemy's minions, we also have to check that if its triggered ability is of type "ENEMY_MINION_ENTER"
        // check there is ritual
        if (enemyRitual != nullptr) {
            auto enemyRitualTrgAbility = enemyRitual->getTrgAbility();

            // check if ritual has trg ability
            if(enemyRitualTrgAbility != nullptr){
                if (enemyRitualTrgAbility->getType()==MINION_ENTER || enemyRitualTrgAbility->getType()==ENEMY_MINION_ENTER) {
                    bool triggered = enemyRitual->useTrgAbility(shared_from_this());
                    if (!triggered) {
                        // print message saying that ritual do not have enoguh charges to continue
                        throw ArgException{"Ritual " + enemyRitual->getName() + " does not have enough charges to be triggered."};
                    }
                }
            } else {
                // if ritual has no trg ability, error
                throw ArgException{"Ritual " + enemyRitual->getName() + " does not have triggered ability."};
            }
        }

        for(auto minion : enemyBoard->getMinions()) {
            // checks if minion has trg ability
            if(minion->hasTrgAbility()) {
                auto trgAbility = minion->getTrgAbility();
                if (trgAbility->getType()==MINION_ENTER || trgAbility->getType()==ENEMY_MINION_ENTER) {
                    trgAbility->effect(shared_from_this(), minion);
                }
            }
        }
    }
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
    if (players.size() <= activePlayer ) {
        throw ArgException{"Player" + to_string(activePlayer) + " cannot be retrieved because it does not exist."};
    }
    
    return players[activePlayer];
}
// get the inactive player
shared_ptr<Player> Game::getInactivePlayer() {
    if (players.size() <= activePlayer ) {
        throw ArgException{"Player" + to_string(1-activePlayer) + " cannot be retrieved because it does not exist."};
    }
    if(activePlayer==0){
        return players[1];
    }
    return players[0];
}

// get player by index
shared_ptr<Player> Game::getPlayer(int index) {
    if (players.size() <= index ) {
        throw ArgException{"Player" + to_string(index) + " cannot be retrieved because it does not exist."};
    }
    return players[index];
}

// destroy the minion
void Game::destroyMinion(std::shared_ptr<Player> player, int minion) {
    auto removed = player->getBoard()->removeMinion(minion);
    removed->die(shared_from_this());
    player->getGraveyard()->addMinionTop(removed->getAttachedMinion());
}

void Game::addMinion(int player, std::shared_ptr<Minion> minion){
    players[player]->getBoard()->addMinionRight(minion);
    checkTriggered(players[player], MINION_ENTER);
}

