#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <memory>

#include "minion.h"
class ActivatedAbility;

///////////////////////////////////////////////////////////////////////////////////////////////////
class Enchantment : public Minion{
    std::string atkChange;
    std::string defChange;
    std::string description;
    protected:
        std::shared_ptr<Minion> component;

    public:
        // Default constructor
        Enchantment();
        // Constructor
        Enchantment(std::string name, int owner, int cost, std::string atkChange, std::string defChange, std::string description);
        //Attach to a Minion(or its Enchantment) component, called by Game::play
        virtual void attach(std::shared_ptr<Minion> minion);
        // Detach the current enchantment from the component and return component, called by Disenchant::effect, 
        // and used when detaching Delay
        std::shared_ptr<Minion> detach();
        // Override Minion::getAttachedMinion
        std::shared_ptr<Minion> getAttachedMinion() override;
        // Override Minion::getEnchanmentList
        std::vector<std::shared_ptr<Enchantment>> getEnchantmentList() override;
        // Getters
        std::string getAtkChange() const;
        std::string getDefChange() const;
        std::string getDescription() const;
        std::shared_ptr<Minion> getComponent() const;
        // Override Minion::computeAtk, computeDef, computeActAbility, computeTrgAbility
        int computeAtk() const override;
        int computeDef() const override;
        virtual std::shared_ptr<ActivatedAbility> computeActAbility() const override;
        virtual std::shared_ptr<TriggeredAbility> computeTrgAbility() const override;
        // Destructor
        ~Enchantment();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class GiantStrength : public Enchantment{
    public:
        explicit GiantStrength(int owner);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Enrage : public Enchantment{
    public:
        explicit Enrage(int owner);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Delay : public Enchantment{
    // Keep the track of number of rounds Delay has been played
    int round = 0;
    public:
        explicit Delay(int owner);
        int getRound() const;
        // Does not restore action to 1, increase round by 1
        void restoreAction() override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class MagicFatigue : public Enchantment{
    public:
        explicit MagicFatigue(int owner);
        // Same as Enchantment::attach, except for creating a new actAbility that costs 2 more than component->getActAbility()
        void attach(std::shared_ptr<Minion> minion) override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Silence : public Enchantment{
    public:
        explicit Silence(int owner);
        // return nullptr
        std::shared_ptr<TriggeredAbility> computeTrgAbility() const override;
        // return nullptr
        std::shared_ptr<ActivatedAbility> computeActAbility() const override;
        
};

#endif
