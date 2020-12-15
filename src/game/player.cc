#include "player.h"
#include "../cardCollections/deck.h"
#include "../cardCollections/board.h"
#include "../cardCollections/graveyard.h"
#include "../cardCollections/hand.h"
#include "../cards/minion/minion.h"
#include "../cards/ritual.h"
#include "../cards/spell.h"
#include "../cards/minion/enchantment.h"
#include "../cards/minion/activatedAbility.h"
#include "game.h"

using namespace std;

Player::Player(string name, int number, shared_ptr<Board> board, shared_ptr<Deck> deck, shared_ptr<Graveyard> graveyard, shared_ptr<Hand> hand)
    : name{name}, life{20}, magic{3}, number{number}, board{board}, deck{deck}, graveyard{graveyard}, hand{hand} {}

string Player::getName() const { return name; }

int Player::getLife() const { return life; }
void Player::setLife(int life) { this->life = life; }

int Player::getMagic() const { return magic; }
void Player::setMagic(int magic) { this->magic = magic; }
bool Player::hasEnoughMagic(int cost) { return magic >= cost; }

int Player::getNumber() const { return number; }

shared_ptr<Board> Player::getBoard() {
    return board;
}
shared_ptr<Deck> Player::getDeck() {
    return deck;
}
shared_ptr<Graveyard> Player::getGraveyard() {
    return graveyard;
}
shared_ptr<Hand> Player::getHand() {
    return hand;
}

// To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
// hand is not full and their deck is not empty.
void Player::draw() {
    if (deck->isEmpty() || hand->isFull()) {
        // throw
        return;
    }
    auto topCard = deck->removeCardTop();
    hand->addCardRight(topCard);
}

void Player::discard(int card) {
    hand->removeCard(card);
}

// Plays the ith card in hand from the left
void Player::play(int card, shared_ptr<Game> game) {
    try { // checks if removeCard is out of range
        auto tmpCard = hand->getCard(card);
        int cost = tmpCard->getCost();

        if(hasEnoughMagic(cost)) {
            // play the card
            if (tmpCard->getType() == "Minion") {

                auto tmpMinion = dynamic_pointer_cast<Minion>(tmpCard);
                bool addSuccess = board->addMinionRight(tmpMinion);
                if (!addSuccess) {
                    // board is full, throw error/print something
                    cout << "board full";
                }
                // otherwise, minion is added to the right
            
            } else if (tmpCard->getType() == "Spell") {
                auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
                tmpSpell->effect(game); // cause the spell effect, then the spell disappears
            
            } else if (tmpCard->getType() == "Ritual") {
                auto tmpRitual = dynamic_pointer_cast<Ritual>(tmpCard);
                board->setRitual(tmpRitual); // sets the ritual to new ritual
            
            } else {
                // throw error, cannot play enchantment without target
            }
            setMagic(getMagic() - cost);
            // remove from hand
            hand->removeCard(card);
        } else {
            // error since not enough magic
        }
    } catch (const out_of_range& oor) {}
}

// Plays the ith card in hand from the left
void Player::play(int card, int player, int target, shared_ptr<Game> game) {
    // checks if removeCard is out of range
    auto tmpCard = hand->getCard(card);
    int cost = tmpCard->getCost();

    // has enough magic cost
    if(hasEnoughMagic(cost)) {
    
        if (tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effectWithTarget(game, player, target); // cause the spell effect, then the spell disappears
        
        } else if (tmpCard->getType() == "Enchantment") {
            auto targetPlayer = game->getPlayer(player);
            auto targetBoard = targetPlayer->getBoard();
            auto targetMinion = targetBoard->getMinion(target);
            auto tmpEnchantment = dynamic_pointer_cast<Enchantment>(tmpCard);

            // attach to the ith game's player's board's target minion
            tmpEnchantment->attach(targetMinion);

            // then point the board minion to the enchantment layer wrapped outside
            targetBoard->setMinion(target, tmpEnchantment);
        } else {
            // throw error, cannot play minion/ritual with target
        }

        // subtract cost
        setMagic(getMagic() - cost);
        // remove from hand
        hand->removeCard(card);
    } else {
        // error since not enough magic
    }

    cout << game->getPlayer(player)->getBoard()->getMinion(0)->getDef() << endl;
}

// play for ritual
void Player::play(int card, int player, shared_ptr<Game> game) {
    // checks if removeCard is out of range
    auto tmpCard = hand->getCard(card);
    int cost = tmpCard->getCost();

    // has enough magic cost
    if(hasEnoughMagic(cost)) {
    
        if (tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effectWithTarget(game, player); // cause the spell effect, then the spell disappears
        
        } else {
            // throw error, cannot play minion/ritual with target
        }

        // subtract cost
        setMagic(getMagic() - cost);
        // remove from hand
        hand->removeCard(card);
    } else {
        // error since not enough magic
    }
}

void Player::use(std::shared_ptr<Game> game, int minion){
    try { // checks if minion is out of range
        auto tmpMinion = board->getMinion(minion);
        int cost  = tmpMinion->getActAbility()->getCost();
        
        if (hasEnoughMagic(cost)) {
            tmpMinion->useAbility(game);
            
            // subtract magic cost
            setMagic(getMagic() - cost);
        }
        
    } catch (const out_of_range& oor) {}
}

void Player::use(std::shared_ptr<Game> game, int minion, int player, int target) {
    try { // checks if minion is out of range
        auto tmpMinion = board->getMinion(minion);
        int cost  = tmpMinion->getActAbility()->getCost();

        if (hasEnoughMagic(cost)) {
            tmpMinion->useAbility(game, player, target);
            
            // subtract magic cost
            setMagic(getMagic() - cost);
        }
        
        // subtract magic cost
    } catch (const out_of_range& oor) {}
}


// use for ritual
void Player::use(std::shared_ptr<Game> game, int minion, int player) {
    // try { // checks if minion is out of range
    //     if (ritual=='r'){
    //         auto tmpMinion = board->getMinion(minion);
    //         tmpMinion->useAbility(player, target);
    //     } else {
    //         // throw error
    //     }
    // } catch (const out_of_range& oor) {}
}