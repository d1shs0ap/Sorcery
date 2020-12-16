#ifndef RITUAL_H
#define RITUAL_H

#include <string>
#include "card.h"

class TriggeredAbility;
class Game;

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
    // Default Constructor
    Ritual();
    // Constructor
    Ritual(std::string name, int owner, int cost, int activationCost, int charges, std::shared_ptr<TriggeredAbility> trgAbility);

    // Getters and Setters
    int getActivationCost();
    int getCharges();
    void setCharges(int newCharges);

    // accessor and mutator for triggered ability
    std::shared_ptr<TriggeredAbility> getTrgAbility() const;
    void setTrgAbility(std::shared_ptr<TriggeredAbility> ability);

    // Trigger the triggered ability while reducing charges, called by Game::checkTriggered 
    bool useTrgAbility(std::shared_ptr<Game> game);

    // Destructor
    ~Ritual();
};

class DarkRitual : public Ritual{
    public:
        explicit DarkRitual(int owner);
};

class AuraOfPower : public Ritual{
    public:
        explicit AuraOfPower(int owner);
};

class Standstill : public Ritual{
    public:
        explicit Standstill(int owner);
};

#endif
