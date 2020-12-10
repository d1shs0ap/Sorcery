#include "deck.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void Deck::loadDeck(ifstream &infile)
{
    string name;
    while (getline(infile, name))
    {
        if (name == "Air Elemental")
        {
        }
    }
}
void Deck::shuffleDeck(){
    // use a time-based seed for the default seed value
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	default_random_engine rng{seed};
    shuffle(cards.begin(), cards.end(), rng);
}

// Checks if deck is empty;
bool Deck::isEmpty(){
    return cards.empty();
}

// Return and remove the top card from the deck, called by draw()
shared_ptr<Card> Deck::removeCardTop() {
    auto tmp = cards.back();
    cards.pop_back();
    return tmp;
}
