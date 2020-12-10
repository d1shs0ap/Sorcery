#include "player.h"

using namespace std;

Player::Player() {}

string Player::getName() const { return name; }

int Player::getLife() const { return life; }
void Player::setLife(int life) { this->life = life; }

int Player::getMagic() const { return magic; }
void Player::setMagic(int magic) { this->magic = magic; }

int Player::getNumber() const { return number; }

// To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
// hand is not full and their deck is not empty.
void Player::draw() {
    auto topCard = deck->removeCardTop();
    hand->addCardRight(topCard);
}

// Plays the ith card in hand from the left
void Player::play(int card) {
    try { // checks if removeCard is out of range
        auto tmpCard = hand->removeCard(card);
        if (tmpCard->getType() == "Minion") {
            auto tmpMinion = dynamic_pointer_cast<Minion>(tmpCard);
            bool addSuccess = board->addMinionRight(tmpMinion);
            if (!addSuccess) {
                // board is full, throw error/print something
            }
            // otherwise, minion is added to the right
        
        } else if (tmpCard->getType() == "Spell") {
            auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
            tmpSpell->effect(); // cause the spell effect, then the spell disappears
        
        } else if (tmpCard->getType() == "Ritual") {
            auto tmpRitual = dynamic_pointer_cast<Ritual>(tmpCard);
            board->setRitual(tmpRitual); // sets the ritual to new ritual
        
        } else {
            // throw error, cannot play enchantment without target
        }
    } catch (const std::out_of_range& oor) {}
}

// Plays the ith card in hand from the left
void Player::play(int card, int player, int target) {
    // checks if removeCard is out of range
    auto tmpCard = hand->removeCard(card);
    if (tmpCard->getType() == "Spell") {
        auto tmpSpell = dynamic_pointer_cast<Spell>(tmpCard);
        tmpSpell->effectWithTarget(player, target); // cause the spell effect, then the spell disappears
    
    } else if (tmpCard->getType() == "Enchantment") {
        auto tmpEnchantment = dynamic_pointer_cast<Enchantment>(tmpCard);
        // attach to the ith game's player's board's target minion
        // tmpEnchantment->attach();
        // then point the board minion to the enchantment layer wrapped outside

    } else {
        // throw error, cannot play minion/ritual with target
    }
}

void Player::use(int minion){
    try { // checks if minion is out of range
        auto tmpMinion = board->getMinion(minion);
        tmpMinion->useAbility();
    } catch (const std::out_of_range& oor) {}
}

void Player::use(int minion, int player, int target) {
    try { // checks if minion is out of range
        auto tmpMinion = board->getMinion(minion);
        tmpMinion->useAbility(player, target);
    } catch (const std::out_of_range& oor) {}
}
