#ifndef DECK_H
#define DECK_H
#include <fstream>
#include <memory>
#include <vector>

#include "../cards/card.h"

class Deck
{
    std::vector<std::shared_ptr<Card>> cards;

public:
    void loadDeck(std::ifstream &infile);
    void shuffle();

    // Checks if deck is empty;
    void isEmpty();

    // Return and remove the top card from the deck, called by draw()
    std::shared_ptr<Card> removeCardTop();
};

#endif
