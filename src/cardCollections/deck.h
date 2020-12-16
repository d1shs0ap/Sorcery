#ifndef DECK_H
#define DECK_H
#include <fstream>
#include <memory>
#include <vector>
#include <random>

class Card;

class Deck {
    // Cards organized from bottom to top
    std::vector<std::shared_ptr<Card>> cards;

    // use a time-based seed for the default seed value
    std::default_random_engine rng;
    int owner;

    public:
        // Constructor
        Deck(std::default_random_engine& rng, int owner);
        
        // Read in card from infile and add them to cards
        void loadDeck(std::ifstream &infile);
        // shuffle cards
        void shuffleDeck();

        // Checks if deck is empty;
        bool isEmpty();
        // Get the length of cards
        int getSize();

        // Return and remove the top card from the deck, called by draw()
        std::shared_ptr<Card> removeCardTop();

        void printDeck();
};

#endif
