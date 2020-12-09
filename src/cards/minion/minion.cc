#include "minion.h"

int Minion::getAtk() const { return atk; }
int Minion::getDef() const { return def; }
void Minion::setDef(int new_def) { def = new_def; }
void Minion::restoreAction() { actions = 1; }

void Minion::attack(Player &other)
{
    if (actions > 0)
    {
        other.setLife(other.getLife() - atk);
        --actions;
    }
}

void Minion::attack(Minion &other)
{
    if (actions > 0)
    {
        other.setDef(other.getDef() - atk);
        --actions;
    }
    def = def - other.getAtk();
}

void Minion::useAbility()
{
}
