#ifndef RITUAL_H
#define RITUAL_H

#include <string>

#include "card.h"
#include "minion/minion.h"
#include "minion/triggeredAbility.h"

// Ritual card
class Ritual : public Card {
    // Cost (of charges) to activate ritual
    int activationCost;
    // Number of charges, consumed when activating ritual
    int charges;
    // Effect (triggered abillity) of ritual;
    TriggeredAbility trgAbility;

public:
    Ritual(int activationCost, int charges, TriggeredAbility trgAbility);

    // accessor and mutator for triggered ability
    TriggeredAbility getTrgAbility() const;
    void setTrgAbility(TriggeredAbility ability);

    // Trigger the triggered ability while reducing charges
    bool useTrgAbility(std::shared_ptr<Game> game);
};

class DarkRitual : Ritual {
    public:
        DarkRitual();
};

class AuraOfPower : Ritual {
    public:
        AuraOfPower();
};

class Standstill : Ritual {
    public:
        Standstill();
};

#endif
