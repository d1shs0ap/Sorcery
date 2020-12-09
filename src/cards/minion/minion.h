#ifndef MINION_H
#define MINION_H

#include "../card.h"
#include "activatedAbility.h"
#include "triggeredAbility.h"
#include "../../game/player.h"

class Minion : public Card
{
    int atk;
    int def;
    // actions is the number of times it is allowed to attack or use an ability in one turn. this can only be 0 or 1 for now.
    unsigned int actions = 0;

    // Activated abilities cost magic and an action point to use, and work similar to playing a spell card.
    ActivatedAbility actAbility;

    // Triggered abilities are activated for free whenever a certain condition is met.
    TriggeredAbility trgAbility;

public:
    int getAtk() const;
    virtual int computeAtk() const = 0;
    void setAtk(int new_atk);
    int getDef() const;
    virtual int computeDef() const = 0;
    void setDef(int new_def);

    virtual ActivatedAbility getActAbility() const = 0;
    void restoreActions();

    void attack(Player &p);
    void attack(Minion &m);
    void useAbility();
};

#endif
