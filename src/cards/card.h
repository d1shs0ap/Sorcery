#ifndef CARD_H
#define CARD_H

#include <string>

// Abstract class for all cards
class Card {
    std::string name;
    std::string type;
    int owner;
    int magicCost;
};

#endif
