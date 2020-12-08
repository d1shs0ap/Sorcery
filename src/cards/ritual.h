#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"
#include "minion/triggeredAbility.h"

// Ritual card
class Ritual : public Card {
    // Cost (of charges) to activate ritual
    int activationCost;
    // Number of charges, consumed when activating ritual
    int charges;
    public:
        // Effect (triggered abillity) of ritual;
        TriggeredAbility effect;
};

#endif