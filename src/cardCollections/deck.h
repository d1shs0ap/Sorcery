#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>

#include "../cards/card.h"

class Deck {
    std::vector<std::shared_ptr<Card>> cards;
    public:
        void loadDeck();
        void shuffle();
};

#endif
