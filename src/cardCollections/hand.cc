#include "hand.h"
#include "../cards/card.h"

using namespace std;

Hand::Hand(){}

// Check if hand is already full
bool Hand::isFull() {
    return (cards.size()==HAND_CAP);
}
        
// Add card to hand, called by draw() in Player
bool Hand::addCardRight(shared_ptr<Card> card){
    if (isFull()){
        // throw exception
        return false;
    }
    cards.push_back(card);
    return true;
}

// Remove a card
void Hand::removeCard(int card) {
    if(cards.size() - 1 < card){
        // then there aren't as many cards as requested index, throw error
    }
    auto tmp = cards[card];
    cards.erase(cards.begin()+card);
}

// Accessor for a single card
shared_ptr<Card> Hand::getCard(int card) {
    if(cards.size() - 1 < card){
        // then there aren't as many cards as requested index, throw error
    }
    return cards[card];
}

// Accessor for cards
vector<shared_ptr<Card>> Hand::getCards() const {
    return cards;
}

// Mutator for cards
void Hand::setCards(vector<shared_ptr<Card>> cards) {
    this->cards = cards;
}