#include "enchantment.h"

Enchantment::Enchantment(std::shared_ptr<Minion> component)
    : component{component} {}
int Enchantment::getAtk() const { return component->getAtk(); }
int Enchantment::getDef() const { return component->getDef(); }
