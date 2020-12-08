#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <memory>

#include "../card.h"
#include "minion.h"

class Enchantment : public Card {
    std::unique_ptr<Minion> enchantedMinion;
};

#endif
