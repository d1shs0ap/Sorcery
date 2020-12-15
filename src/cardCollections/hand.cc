#include "hand.h"
#include "../cards/card.h"
#include "../argException.h"

using namespace std;

Hand::Hand(){}

// Check if hand is already full
bool Hand::isFull() {
    return (cards.size()==HAND_CAP);
}
        
// Add card to hand, called by draw() in Player
void Hand::addCardRight(shared_ptr<Card> card){
    if (isFull()){
        // throw exception
        throw ArgException{"Card cannot be added to hand because hand is full."};
    }
    cards.push_back(card);
}

// Remove a card
void Hand::removeCard(int card) {
    if(cards.size() - 1 < card){
        // then there aren't as many cards as requested index, throw error
        throw ArgException{"Card " + to_string(card) + " cannot removed from hand because it does not exist."};
    }
    auto tmp = cards[card];
    cards.erase(cards.begin()+card);
}

// Accessor for a single card
shared_ptr<Card> Hand::getCard(int card) {
    if(cards.size() - 1 < card){
        // then there aren't as many cards as requested index, throw error
        throw ArgException{"Card " + to_string(card) + " cannot retrieved from hand because it does not exist."};
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