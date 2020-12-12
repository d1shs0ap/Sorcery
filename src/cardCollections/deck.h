#ifndef DECK_H
#define DECK_H
#include <fstream>
#include <memory>
#include <vector>

#include "../cards/card.h"
#include "../cards/minion/minion.h"

class Deck {
    // Cards organized from bottom to top
    std::vector<std::shared_ptr<Card>> cards;

    // use a time-based seed for the default seed value
    unsigned seed;
    int owner;

    public:
        Deck(unsigned seed, int owner);

        void loadDeck(std::ifstream &infile);
        void shuffleDeck();

        // Checks if deck is empty;
        bool isEmpty();

        // Return and remove the top card from the deck, called by draw()
        std::shared_ptr<Card> removeCardTop();
};

#endif
