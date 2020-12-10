#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "../cards/card.h"

const int HAND_CAP = 5;

class Hand {
    std::vector<std::shared_ptr<Card>> cards;

    public:
        bool isFull();

        // Add card to hand, called by draw() in Player
        void addCardRight(std::shared_ptr<Card> card);
        
        // Accessor and mutator methods for cards
        std::vector<std::shared_ptr<Card>> getCards();
        void setCards(std::vector<std::shared_ptr<Card>> cards);
};

#endif
