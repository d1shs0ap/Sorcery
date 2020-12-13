#ifndef RITUAL_H
#define RITUAL_H

#include <string>
#include "card.h"
#include "minion/triggeredAbility.h"

// Ritual card
class Ritual : public Card, public std::enable_shared_from_this<Ritual>
{
    // Cost (of charges) to activate ritual
    int activationCost;
    // Number of charges, consumed when activating ritual
    int charges;
    // Effect (triggered abillity) of ritual;
    std::shared_ptr<TriggeredAbility> trgAbility;

public:
    Ritual(std::string name, int owner, int cost,
           int activationCost, int charges, std::shared_ptr<TriggeredAbility> trgAbility);

    int getActivationCost();
    int getCharges();

    // accessor and mutator for triggered ability
    std::shared_ptr<TriggeredAbility> getTrgAbility() const;
    void setTrgAbility(std::shared_ptr<TriggeredAbility> ability);

    // Trigger the triggered ability while reducing charges
    bool useTrgAbility(std::shared_ptr<Game> game);

    virtual ~Ritual();
};

class DarkRitual : Ritual
{
public:
    explicit DarkRitual(int owner);
};

class AuraOfPower : Ritual
{
public:
    explicit AuraOfPower(int owner);
};

class Standstill : Ritual
{
public:
    explicit Standstill(int owner);
};

#endif
