#ifndef ABILITY_H
#define ABILITY_H
#include <string>

#include "observer.h"

class ActivatedAbility
{
private:
    std::string expression;
    unsigned int costMagic;
};

class TriggeredAbility : public Observer
{
private:
    std::string expression;
};

#endif