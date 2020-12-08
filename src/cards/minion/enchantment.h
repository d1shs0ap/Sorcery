#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <memory>

#include "minion.h"

class Enchantment : public Minion {
    std::shared_ptr<Minion> enchantedMinion;
};

#endif
