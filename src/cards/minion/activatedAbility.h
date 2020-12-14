#ifndef ACTIVATED_ABILITY_H
#define ACTIVATED_ABILITY_H

#include <string>
#include <vector>
#include <memory>
#include <exception>

class Game;
class Card;
class Minion;

struct ActAbilityArgExn{
    std::string message;
    ActAbilityArgExn(std::string message);
};

class ActivatedAbility{
    std::string description;
    int cost;


    public:
        ActivatedAbility();
        ActivatedAbility(std::string description, int cost);
        std::string getDescription() const;
        int getCost() const;
        void setCost(int newCost);
        virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const;
        virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion,  std::shared_ptr<Minion> target) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class DamageTarget : public ActivatedAbility{
    public:
        DamageTarget();
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion,  std::shared_ptr<Minion> target) const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class SummonOneAirElemental : public ActivatedAbility{
    public:
        SummonOneAirElemental();
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion,  std::shared_ptr<Minion> target) const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class SummonThreeAirElemental : public ActivatedAbility{
    public:
        SummonThreeAirElemental();
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const override;
        void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion,  std::shared_ptr<Minion> target) const override;
};

#endif
