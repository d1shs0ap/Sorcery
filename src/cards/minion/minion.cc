#include "minion.h"

int Minion::getAtk() const { return atk; }
int Minion::computeAtk() const { return getAtk(); }
void Minion::setAtk(int new_atk) { atk = new_atk; }
int Minion::getDef() const { return def; }
int Minion::computeDef() const { return getDef(); }
void Minion::setDef(int new_def) { def = new_def; }

ActivatedAbility Minion::getActAbility() const { return actAbility; }
void Minion::restoreActions() { actions = 1; }

void Minion::attack(Player &other)
{
    if (actions > 0)
    {
        int attack = this->computeAtk();
        other.setLife(other.getLife() - attack);
        --actions;
    }
}

void Minion::attack(Minion &other)
{
    int attack = this->computeAtk();
    if (actions > 0)
    {
        other.setDef(other.computeDef() - attack);
        --actions;
    }
    def = def - other.computeAtk();
}

void Minion::useAbility()
{
}
