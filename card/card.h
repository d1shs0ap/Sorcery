#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
private:
    std::string name;
    unsigned int costMagic;
    // A card’s type is one of “minion,” “enchantment,” “ritual,” or “spell.”
    std::string type;
};

#endif
