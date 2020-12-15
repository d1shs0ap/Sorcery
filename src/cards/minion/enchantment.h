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
        Enchantment();
        Enchantment(std::string name, int owner, int cost, std::string atkChange, std::string defChange, std::string description);
        virtual void attach(std::shared_ptr<Minion> minion);
        std::shared_ptr<Minion> detach();
        std::shared_ptr<Minion> getAttachedMinion() override;
        std::vector<std::shared_ptr<Enchantment>> getEnchantmentList() override;
        std::string getAtkChange() const;
        std::string getDefChange() const;
        std::string getDescription() const;
        std::shared_ptr<Minion> getComponent() const;
        int computeAtk() const override;
        int computeDef() const override;
        virtual std::shared_ptr<ActivatedAbility> computeActAbility() const override;
        virtual std::shared_ptr<TriggeredAbility> computeTrgAbility() const override;
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
    int round = 0;
    public:
        explicit Delay(int owner);
        int getRound() const;
        void restoreAction() override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class MagicFatigue : public Enchantment{
    public:
        explicit MagicFatigue(int owner);
        void attach(std::shared_ptr<Minion> minion) override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Silence : public Enchantment{
    public:
        explicit Silence(int owner);
        std::shared_ptr<TriggeredAbility> computeTrgAbility() const override;
        std::shared_ptr<ActivatedAbility> computeActAbility() const override;
        
};

#endif
