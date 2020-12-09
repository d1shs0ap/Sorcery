#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <memory>

#include "minion.h"

class Enchantment : public Minion
{
    std::shared_ptr<Minion> component;

public:
    Enchantment(std::shared_ptr<Minion> component);
    virtual int getAtk() const override;
    virtual int getDef() const override;
};

#endif
