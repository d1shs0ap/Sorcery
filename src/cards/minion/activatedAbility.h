#ifndef ACTIVATED_ABILITY_H
#define ACTIVATED_ABILITY_H

#include <string>

class ActivatedAbility {
    std::string description;
    int magicCost;

    public:
        void effect();
};

#endif