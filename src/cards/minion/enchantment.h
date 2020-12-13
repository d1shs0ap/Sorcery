#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <memory>

#include "minion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class Enchantment : public Minion{

    protected:
        std::shared_ptr<Minion> component;

    public:
        Enchantment();
        void attach(std::shared_ptr<Minion> minion);
        virtual ~Enchantment();
        // gets minion enchantment is attached to
        std::shared_ptr<Minion> getAttachedMinion();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class GiantStrength : public Enchantment{
    const int atkBoost = 2;
    const int defBoost = 2; 

    public:
        virtual int computeAtk() const override;
        virtual int computeDef() const override;
        virtual std::vector<std::string> getDisplay() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Enrage : public Enchantment{
    const int atkScale;
    const int defWound;
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
