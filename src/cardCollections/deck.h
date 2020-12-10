#ifndef DECK_H
#define DECK_H
#include <fstream>
#include <memory>
#include <vector>

#include "../cards/card.h"

class Deck {
    // Cards organized from bottom to top
    std::vector<std::shared_ptr<Card>> cards;

    public:
        void loadDeck(std::ifstream &infile);
        void shuffleDeck();

        // Checks if deck is empty;
        bool isEmpty();

        // Return and remove the top card from the deck, called by draw()
        std::shared_ptr<Card> removeCardTop();
};

#endif
