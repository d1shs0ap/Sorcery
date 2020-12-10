#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "../cards/card.h"

const int HAND_CAP = 5;

class Hand {
    // cards in hand, ordered from left to right (cards[0] is the leftmost and cards[last] is the rightmost)
    std::vector<std::shared_ptr<Card>> cards;

    public:
        bool isFull();

        // Add card to hand, called by draw() in Player
        // Returns true if successfully drawn (hand not full), otherwise return false
        bool addCardRight(std::shared_ptr<Card> card);
        
        // Removes single card
        std::shared_ptr<Card> removeCard(int i);

        // Accessor and mutator methods for cards
        std::vector<std::shared_ptr<Card>> getCards() const;
        void setCards(std::vector<std::shared_ptr<Card>> cards);
};

#endif
