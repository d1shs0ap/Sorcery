#include "hand.h"

using namespace std;

// Check if hand is already full
bool Hand::isFull() {
    return (cards.size()==HAND_CAP);
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
std::shared_ptr<Card> Hand::removeCard(int card)  {
    if(cards.size() - 1 < card){
        // then there aren't as many cards as requested index, throw error
    }
    auto tmp = cards[card];
    cards.erase(cards.begin()+card);
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