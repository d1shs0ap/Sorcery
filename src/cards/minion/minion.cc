#include "minion.h"

void Minion::setDef(int new_def) { def = new_def; }

void Minion::attack(Player &p)
{
    if (actions > 0)
    {
        p.setLife(p.getLife() - atk);
    }
}

void Minion::attack(Minion &m)
{
}

void Minion::useAbility()
{
}

void Minion::restoreAction()
{
}
