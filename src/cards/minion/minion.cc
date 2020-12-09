#include "minion.h"

int Minion::getAtk() const { return atk; }
int Minion::getDef() const { return def; }
ActivatedAbility Minion::getActAbility() const { return actAbility; }

void Minion::setDef(int new_def) { def = new_def; }
void Minion::restoreActions() { actions = 1; }

void Minion::attack(Player &other)
{
    /* got some problem here..
    if (actions > 0)
    {
        other.setLife(other.getLife() - this->getAtk());
        --actions;
    }
    */
}

void Minion::attack(Minion &other)
{
    /* got some problem here..
    int attack = this->getAtk();
    if (actions > 0)
    {
        other.setDef(other.getDef() - attack);
        --actions;
    }
    def = def - other.getAtk();
    */
}

void Minion::useAbility()
{
}
