#include "deck.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "../cards/minion/minion.h"
#include "../cards/card.h"

using namespace std;

Deck::Deck(unsigned seed, int owner)
    : seed{seed}, owner{owner} {}

void Deck::loadDeck(ifstream &infile)
{
    string cardName;
    while (getline(infile, cardName))
    {
        if (cardName=="Air Elemental") {
            auto card = make_shared<AirElemental>(owner);
            cards.push_back(card);
        } else if (cardName=="Earth Elemental") {
            auto card = make_shared<EarthElemental>(owner);
            cards.push_back(card);
        } else if (cardName=="Bomb") {
            auto card = make_shared<Bomb>(owner);
            cards.push_back(card);
        } else if (cardName=="Fire Elemental") {
            auto card = make_shared<FireElemental>(owner);
            cards.push_back(card);
        } else if (cardName=="Potion Seller") {
            auto card = make_shared<PotionSeller>(owner);
            cards.push_back(card);
        } else if (cardName=="Novice Pyromancer") {
            auto card = make_shared<NovicePyromancer>(owner);
            cards.push_back(card);
        } else if (cardName=="Apprentice Summoner") {
            auto card = make_shared<ApprenticeSummoner>(owner);
            cards.push_back(card);
        } else if (cardName=="Master Summoner") {
            auto card = make_shared<MasterSummoner>(owner);
            cards.push_back(card);
        }
        // } else if (cardName=="") {
        //     auto card = make_shared<>(owner);
        //     cards.push_back(card);
        // } else if (cardName=="") {
        //     auto card = make_shared<>(owner);
        //     cards.push_back(card);
        // } else if (cardName=="") {
        //     auto card = make_shared<>(owner);
        //     cards.push_back(card);
        // } else if (cardName=="") {
        //     auto card = make_shared<>(owner);
        //     cards.push_back(card);
        // } else if (cardName=="") {
        //     auto card = make_shared<>(owner);
        //     cards.push_back(card);
        // } else if (cardName=="") {
        //     auto card = make_shared<>(owner);
        //     cards.push_back(card);
        // } else if (cardName=="") {
        //     auto card = make_shared<>(owner);
        //     cards.push_back(card);
        // }
    }

    if(cards.size() < 5) {
        // throw error "too few cards"
    }
}


void Deck::shuffleDeck(){
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

void Deck::printDeck() {
    cout << "Owner" << owner << endl;
    for (auto card : cards){
        cout << card->getName() << endl;
    }
}
