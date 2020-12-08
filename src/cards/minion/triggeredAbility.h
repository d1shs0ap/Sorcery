#ifndef TRIGGERED_ABILITY_H
#define TRIGGERED_ABILITY_H

#include <string>

class TriggeredAbility {
    // Description of the ability displayed on the view
    std::string description;

    public:
        // Effect when ability is triggered
        void effect();
        // Conditions for trigger
        bool checkCondition();
};

#endif
