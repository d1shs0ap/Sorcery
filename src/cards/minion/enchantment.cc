#include "enchantment.h"

Enchantment::Enchantment(std::shared_ptr<Minion> component)
    : component{component} {}
int Enchantment::computeAtk() const { return component->computeAtk(); }
int Enchantment::computeDef() const { return component->computeDef(); }
