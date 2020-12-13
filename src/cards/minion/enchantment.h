#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <memory>

#include "minion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class Enchantment : public Minion{
    std::string atkChange;
    std::string defChange;
    protected:
        std::shared_ptr<Minion> component;

    public:
        Enchantment();
        void attach(std::shared_ptr<Minion> minion);
        std::shared_ptr<Minion> getAttachedMinion();
        std::string getAtkChange();
        std::string getDefChange();
        virtual ~Enchantment();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class GiantStrength : public Enchantment{

    public:
        virtual int computeAtk() const override;
        virtual int computeDef() const override;
        virtual std::vector<std::string> getDisplay() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Enrage : public Enchantment{
    public:
        virtual int computeAtk() const override;
        virtual int computeDef() const override;
        virtual std::vector<std::string> getDisplay() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Delay : public Enchantment
{
    // may need more private fields.
public:
    virtual std::vector<std::string> getDisplay() const override;
};

#endif
