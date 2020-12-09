#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "../cards/card.h"

class Hand {
    std::vector<std::shared_ptr<Card>> cards;
    public:
        bool isFull();
        
        std::vector<std::shared_ptr<Card>> getCards();
        void setCards(std::vector<std::shared_ptr<Card>> cards);

        // Add card to hand, called by draw() in Player
        void addCardRight(std::shared_ptr<Card> card);
};

#endif
