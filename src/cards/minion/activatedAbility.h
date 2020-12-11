#ifndef ACTIVATED_ABILITY_H
#define ACTIVATED_ABILITY_H

#include <string>

class ActivatedAbility
{
    std::string description;
    int cost;
    std::shared_ptr<Minion> minion;


public:
    ActivatedAbility();
    ActivatedAbility(std::string description, int cost);
    std::string getDescription() const;
    int getCost() const;
    virtual void effect(Game game) const;
    virtual void effect(Card card) const;
};

#endif
