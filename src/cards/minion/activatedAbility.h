#ifndef ACTIVATED_ABILITY_H
#define ACTIVATED_ABILITY_H

#include <string>
#include <vector>
#include <memory>
#include <exception>

class Game;
class Card;
class Minion;

class ActivatedAbility{
    std::string description;
    int cost;


    public:
        // Default constructor 
        ActivatedAbility();
        // Constructor
        ActivatedAbility(std::string description, int cost);
        // Getters
        std::string getDescription() const;
        int getCost() const;
        // Setter
        void setCost(int newCost);
        // Making effect, called by Minion::useAbility
        virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const;
        virtual void effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion,  std::shared_ptr<Minion> target) const;
        // Destructor
        virtual ~ActivatedAbility();
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
