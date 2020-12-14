#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <memory>

#include "minion.h"

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
        void attach(std::shared_ptr<Minion> minion);
        std::shared_ptr<Minion> getAttachedMinion() override;
        std::vector<std::shared_ptr<Enchantment>> getEnchantmentList() override;
        std::string getAtkChange() const;
        std::string getDefChange() const;
        std::string getDescription() const;
        int computeAtk() const override;
        int computeDef() const override;
        ~Enchantment();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class GiantStrength : public Enchantment{
    GiantStrength(int owner);
    public:
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Enrage : public Enchantment{
    Enrage(int owner);
    public:
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


#endif
