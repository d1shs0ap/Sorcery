#include "enchantment.h"

Enchantment::Enchantment(std::shared_ptr<Minion> component)
    : Minion{0, 0}, component{component} {}
