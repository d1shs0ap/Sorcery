#ifndef MINION_H
#define MINION_H

#include "ability.h"
#include "subject.h"

class Minion : public Subject
{
private:
    int atk; // I simplified this. The var name is different from the UML.
    int def; // I simplified this. The var name is different from the UML.
    int action;
    ActivatedAbility actAbility;
    TriggeredAbility trgAbility;
};

#endif
