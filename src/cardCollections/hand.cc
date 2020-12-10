#include "hand.h"

using namespace std;

// Check if hand is already full
bool Hand::isFull() {
    if (cards.size()==HAND_CAP){
        return true;
    }
    return false;
}
        
// Add card to hand, called by draw() in Player
bool Hand::addCardRight(shared_ptr<Card> card){
    if (isFull()){ 
        return false;
    }
    cards.push_back(card);
    return true;
}

// Accessor for a single card
std::shared_ptr<Card> Hand::removeCard(int i)  {
    auto tmp = cards[i];
    cards.erase(cards.begin()+i);
    return tmp;
}

// Accessor for cards
vector<shared_ptr<Card>> Hand::getCards() const {
    return cards;
}

// Mutator for cards
void Hand::setCards(vector<shared_ptr<Card>> cards) {
    this->cards = cards;
}