#ifndef MINION_H
#define MINION_H

#include "ability.h"
#include "card.h"
#include "player.h"
#include "subject.h"

class Minion : public Card, Subject
{
private:
    unsigned int atk; // simplified variable name. this is different from the UML.
    unsigned int def; // simplified variable name. this is different from the UML.
    unsigned int action;
    ActivatedAbility actAbility;
    TriggeredAbility trgAbility;

public:
    void attack(Player &p);
    void attack(Minion &m);
    void use();
    void actionResort();
};

#endif
