#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>

#include "ability.h"
#include "decorator.h"

class Enchantment : public Decorator
{
private:
    std::string atkChange; // ? why string?
    std::string defChange;
    ActivatedAbility actAbility;
};

#endif
