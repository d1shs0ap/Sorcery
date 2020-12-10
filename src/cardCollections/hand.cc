#include "hand.h"

// Check if hand is already full
bool Hand::isFull() {
    if (cards.size()==HAND_CAP){
        return true;
    }
    return false;
}
        
// Add card to hand, called by draw() in Player
bool Hand::addCardRight(std::shared_ptr<Card> card){
    if (isFull()){ 
        return false;
    }
    cards.push_back(card);
    return true;
}

// Accessor for cards
std::vector<std::shared_ptr<Card>> Hand::getCards() {
    return cards;
}

// Mutator for cards
void Hand::setCards(std::vector<std::shared_ptr<Card>> cards) {
    cards.clear();
    this->cards = cards;
}