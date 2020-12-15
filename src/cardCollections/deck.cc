#include "deck.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "../cards/minion/minion.h"
#include "../cards/minion/enchantment.h"
#include "../cards/ritual.h"
#include "../cards/spell.h"
#include "../cards/card.h"
#include "../argException.h"


using namespace std;

Deck::Deck(default_random_engine& rng, int owner)
    : rng{rng}, owner{owner} {}

void Deck::loadDeck(ifstream &infile)
{
    string cardName;
    while (getline(infile, cardName)) {   
        // minions
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
        // Enchantments
        else if (cardName=="Giant Strength") {
            auto card = make_shared<GiantStrength>(owner);
            cards.push_back(card);
        } else if (cardName=="Enrage") {
            auto card = make_shared<Enrage>(owner);
            cards.push_back(card);
        } else if (cardName=="Magic Fatigue") {
            auto card = make_shared<MagicFatigue>(owner);
            cards.push_back(card);
        } else if (cardName=="Delay") {
            auto card = make_shared<Delay>(owner);
            cards.push_back(card);
        } else if (cardName=="Silence") {
            auto card = make_shared<Silence>(owner);
            cards.push_back(card);
        } 
        // Rituals
        else if (cardName=="Dark Ritual") {
            auto card = make_shared<DarkRitual>(owner);
            cards.push_back(card);
        } else if (cardName=="Aura of Power") {
            auto card = make_shared<AuraOfPower>(owner);
            cards.push_back(card);
        } else if (cardName=="Standstill") {
            auto card = make_shared<Standstill>(owner);
            cards.push_back(card);
        }
        // Spells
        else if (cardName=="Banish") {
            auto card = make_shared<Banish>(owner);
            cards.push_back(card);
        } else if (cardName=="Unsummon") {
            auto card = make_shared<Unsummon>(owner);
            cards.push_back(card);
        } else if (cardName=="Recharge") {
            auto card = make_shared<Recharge>(owner);
            cards.push_back(card);
        } else if (cardName=="Disenchant") {
            auto card = make_shared<Disenchant>(owner);
            cards.push_back(card);
        } else if (cardName=="RaiseDead") {
            auto card = make_shared<RaiseDead>(owner);
            cards.push_back(card);
        } else if (cardName=="Blizzard") {
            auto card = make_shared<Blizzard>(owner);
            cards.push_back(card);
        }
    }
}


void Deck::shuffleDeck(){
    shuffle(cards.begin(), cards.end(), rng);
}

// Checks if deck is empty;
bool Deck::isEmpty(){
    return cards.empty();
}

// Return and remove the top card from the deck, called by draw()
shared_ptr<Card> Deck::removeCardTop() {
    if (!isEmpty()){
        auto tmp = cards.back();
        cards.pop_back();
        return tmp;
    } else {
        throw ArgException{"Card cannot be drawn from deck because deck is empty."};
    }
}

void Deck::printDeck() {
    cout << "Owner" << owner << endl;
    for (auto card : cards){
        cout << card->getName() << endl;
    }
}
