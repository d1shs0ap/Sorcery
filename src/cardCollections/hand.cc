#include "hand.h"

// Check if hand is already full
bool Hand::isFull() {
    if (cards.size()==HAND_CAP){
        return true;
    }
    return false;
}
        
// Add card to hand, called by draw() in Player
void Hand::addCardRight(std::shared_ptr<Card> card){}

// Accessor for cards
std::vector<std::shared_ptr<Card>> Hand::getCards() {
    
}
// Mutator for cards
void Hand::setCards(std::vector<std::shared_ptr<Card>> cards);