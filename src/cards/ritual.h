#ifndef RITUAL_H
#define RITUAL_H

#include <string>

#include "card.h"
#include "minion/minion.h"
#include "minion/triggeredAbility.h"

// Ritual card
class Ritual : public Card, std::enable_shared_from_this<Minion> {
    // Cost (of charges) to activate ritual
    int activationCost;
    // Number of charges, consumed when activating ritual
    int charges;
    // Effect (triggered abillity) of ritual;
    TriggeredAbility trgAbility;

public:
    Ritual(std::string name, int owner, int cost, int activationCost, int charges, TriggeredAbility trgAbility);

    // accessor and mutator for triggered ability
    TriggeredAbility getTrgAbility() const;
    void setTrgAbility(TriggeredAbility ability);

    // Trigger the triggered ability while reducing charges
    bool useTrgAbility(std::shared_ptr<Game> game);
};

class DarkRitual : Ritual {
    public:
        explicit DarkRitual(int owner);
};

class AuraOfPower : Ritual {
    public:
        explicit AuraOfPower(int owner);
};

class Standstill : Ritual {
    public:
        explicit Standstill(int owner);
};

#endif
