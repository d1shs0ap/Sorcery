#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <memory>

#include "minion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
class Enchantment : public Minion
{
    std::shared_ptr<Minion> component;

    std::string atkChanges;
    std::string defChanges;

public:
    Enchantment();
    void attach(std::shared_ptr<Minion> minion);
    int computeAtk();
    int computeDef();
    void update();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class GiantStrength : public Enchantment
{


public:
    virtual int computeAtk() const override;
    virtual int computeDef() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Enrage : public Enchantment
{


public:
    virtual int computeAtk() const override;
    virtual int computeDef() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
