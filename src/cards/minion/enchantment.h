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
    void update();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class GiantStrength : public Enchantment
{


public:
    int computeAtk() const override;
    int computeDef() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
class Enrage : public Enchantment
{


public:
    int computeAtk() const override;
    int computeDef() const override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
