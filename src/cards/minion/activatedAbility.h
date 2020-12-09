#ifndef ACTIVATED_ABILITY_H
#define ACTIVATED_ABILITY_H

#include <string>

class ActivatedAbility
{
    std::string description;
    int cost;

public:
    ActivatedAbility();
    ActivatedAbility(std::string description, int cost);
    std::string getDescription();
    int getCost();
    void effect();
};

#endif
