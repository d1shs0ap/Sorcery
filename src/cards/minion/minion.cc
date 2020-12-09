#include "minion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Minion::Minion(int atk, int def)
    : atk{atk}, def{def} {}

int Minion::getAtk() const { return atk; }
void Minion::setAtk(int new_atk) { atk = new_atk; }
int Minion::getDef() const { return def; }
void Minion::setDef(int new_def) { def = new_def; }

ActivatedAbility Minion::getActAbility() const { return actAbility; }
void Minion::restoreActions() { actions = actionsCap; }

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
    if (actions > 0)
    {
        other.setDef(other.getDef() - this->computeAtk());
        --actions;
    }
    this->setDef(this->getDef() - other.computeAtk());
}

void Minion::useAbility()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
const int AirElementalAtk = 1;
const int AirElementalDef = 1;
AirElemental::AirElemental()
    : Minion{1, 1} {}
