#ifndef ACTIVATED_ABILITY_H
#define ACTIVATED_ABILITY_H

#include <string>
#include "minion.h"
#include "../card.h"
#include "../../game/game.h"

class ActivatedAbility
{
    std::string description;
    int cost;
    std::shared_ptr<Minion> minion;


public:
    ActivatedAbility();
    ActivatedAbility(std::string description, int cost, std::shared_ptr<Minion> minion);
    std::string getDescription() const;
    int getCost() const;
    virtual void effect(Game game) const;
    virtual void effect(Card card) const;
};

class DamageTarget : public ActivatedAbility{
    public:
        DamageTarget(std::shared_ptr<Minion> minion);
        void effect(Game game) const override;
        void effect(Card card) const override;


};
#endif
