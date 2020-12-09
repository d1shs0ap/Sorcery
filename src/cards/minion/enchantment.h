#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <memory>

#include "minion.h"

class Enchantment : public Minion
{
    std::shared_ptr<Minion> component;

public:
    Enchantment(std::shared_ptr<Minion> component);
    virtual int computeAtk() const override;
    virtual int computeDef() const override;
};

#endif
