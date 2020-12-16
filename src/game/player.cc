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
#include "../argException.h"

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
    if (board==nullptr){
        throw ArgException{"Board does not exist for player " + (getName()) + "."};
    }
    return board;
}
shared_ptr<Deck> Player::getDeck() {
    if (deck==nullptr){
        throw ArgException{"Deck does not exist for player " + (getName()) + "."};
    }
    return deck;
}
shared_ptr<Graveyard> Player::getGraveyard() {
    if (graveyard==nullptr){
        throw ArgException{"Graveyard does not exist for player " + (getName()) + "."};
    }
    return graveyard;
}
shared_ptr<Hand> Player::getHand() {
    if (hand==nullptr){
        throw ArgException{"Hand does not exist for player " + (getName()) + "."};
    }
    return hand;
}

// To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
// hand is not full and their deck is not empty.
void Player::draw() {
    if (hand->isFull()) {
        throw ArgException{"Card cannot be added to hand because hand is full."};
    }
    auto topCard = deck->removeCardTop();
    hand->addCardRight(topCard);
}

void Player::discard(int card) {
    hand->removeCard(card);
}

// Plays the ith card in hand from the left
void Player::play(int card, shared_ptr<Game> game, bool testing) {
    auto tmpCard = hand->getCard(card);
    int cost = tmpCard->getCost();

    // normal mode
    if(hasEnoughMagic(cost)) {
        // play the card
        if (tmpCard->getType() == "Minion") {

            auto tmpMinion = dynamic_pointer_cast<Minion>(tmpCard);
            board->addMinionRight(tmpMinion);
        
        } else if (tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effect(game); // cause the spell effect, then the spell disappears
        
        } else if (tmpCard->getType() == "Ritual") {
            auto tmpRitual = dynamic_pointer_cast<Ritual>(tmpCard);
            board->setRitual(tmpRitual); // sets the ritual to new ritual
        
        } else {
            // throw error, cannot play enchantment without target
            throw ArgException{"play [card] only works with minions, spells, and rituals."};
        }
        setMagic(getMagic() - cost);
        // remove from hand
        hand->removeCard(card);
    } else {
        // if testing mode and we are playing a spell
        if(testing && tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effect(game); // cause the spell effect, then the spell disappears
            
            // subtract cost
            setMagic(0);
            // remove from hand
            hand->removeCard(card);
        } else {
            throw ArgException{"Not enough magic."};
        }
    }
}

// Plays the ith card in hand from the left
void Player::play(int card, int player, int target, shared_ptr<Game> game, bool testing) {
    // checks if removeCard is out of range
    auto tmpCard = hand->getCard(card);
    int cost = tmpCard->getCost();

    // has enough magic cost
    if(hasEnoughMagic(cost)) {
    
        if (tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effect(game, player, target); // cause the spell effect, then the spell disappears
        
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
            throw ArgException{"play [card] [target-player] [target-minion] only works with spells and enchantments."};
        }

        // subtract cost
        setMagic(getMagic() - cost);
        // remove from hand
        hand->removeCard(card);
    } else {
        // if testing mode and we are playing a spell
        if(testing && tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effect(game, player, target); // cause the spell effect, then the spell disappears
            
            // subtract cost
            setMagic(0);
            // remove from hand
            hand->removeCard(card);
        } else {
            // error since not enough magic
            throw ArgException{"Not enough magic."};
        }
    }
}

// play for ritual
void Player::play(int card, int player, shared_ptr<Game> game, bool testing) {
    // checks if removeCard is out of range
    auto tmpCard = hand->getCard(card);
    int cost = tmpCard->getCost();

    // if ritual does not exist
    if(game->getPlayer(player)->getBoard()->getRitual()==nullptr){
        throw ArgException{"Ritual does not exist."};
    }

    // has enough magic cost
    if(hasEnoughMagic(cost)) {
    
        if (tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effect(game, player); // cause the spell effect, then the spell disappears
        
        } else {
            // throw error, cannot play minion/ritual with target
            throw ArgException{"play [card] [target-player] [target-ritual] only works with spells."};
        }

        // subtract cost
        setMagic(getMagic() - cost);
        // remove from hand
        hand->removeCard(card);
    } else {
        // if testing mode and we are playing a spell
        if(testing && tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effect(game, player); // cause the spell effect, then the spell disappears
            
            // subtract cost
            setMagic(0);
            // remove from hand
            hand->removeCard(card);
        } else {
            // error since not enough magic
            throw ArgException{"Not enough magic."};
        }
    }
}

void Player::use(std::shared_ptr<Game> game, int minion, bool testing){
    auto tmpMinion = board->getMinion(minion);
    int cost = tmpMinion->getActAbility()->getCost();
    
    if (hasEnoughMagic(cost)) {
        tmpMinion->useAbility(game);

        // subtract magic cost
        setMagic(getMagic() - cost);
    } else {
        if (testing) {
            tmpMinion->useAbility(game);
            // subtract magic cost
            setMagic(0);
        }
        // error since not enough magic
        throw ArgException{"Not enough magic."};
    }
}

void Player::use(std::shared_ptr<Game> game, int minion, int player, int target, bool testing) {
    auto tmpMinion = board->getMinion(minion);
    int cost  = tmpMinion->getActAbility()->getCost();

    if (hasEnoughMagic(cost)) {
        tmpMinion->useAbility(game, player, target);
        
        // subtract magic cost
        setMagic(getMagic() - cost);
    } else {
        if (testing) {
            tmpMinion->useAbility(game);
            // subtract magic cost
            setMagic(0);
        }
        // error since not enough magic
        throw ArgException{"Not enough magic."};
    }
    
    // subtract magic cost
}

