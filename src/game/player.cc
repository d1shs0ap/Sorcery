#include "player.h"

using namespace std;

Player::Player() {}

string Player::getName() const { return name; }

int Player::getLife() const { return life; }
void Player::setLife(int life) { this->life = life; }

int Player::getLife() const { return magic; }
void Player::setLife(int magic) { this->magic = magic; }

// To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
// hand is not full and their deck is not empty.
void Player::draw() {
    auto topCard = deck->removeCardTop();
    hand->addCardRight(topCard);
}

// Plays the ith card in hand from the left
void Player::play(int i) {
    auto tmpCard = hand->removeCard(i);
    if (tmpCard->getType() == "Minion") {
        auto tmpMinion = dynamic_pointer_cast<Minion>(tmpCard);

        
    } else if (tmpCard->getType() == "Spell") {
        auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
        tmpSpell->effect();
    } else if (tmpCard->getType() == "Ritual") {
        auto tmpRitual = dynamic_pointer_cast<Ritual>(tmpCard);
        tmpRitual

    } else if (tmpCard->getType() == "Enchantment") {

    } // what if none?
}
