#include "minion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Minion::Minion(std::string name, int owner, int cost, int atk, int def) : 
    Card{name, "Minion", owner, cost}, atk{atk}, def{def} {}

int Minion::getAtk() const { return atk; }
int Minion::computeAtk() const { return getAtk(); }
void Minion::setAtk(int new_atk) { atk = new_atk; }
int Minion::getDef() const { return def; }
int Minion::computeDef() const { return getDef(); }
void Minion::setDef(int new_def) { def = new_def; }

void Minion::restoreActions() { actions = actionsCap; }
ActivatedAbility Minion::getActAbility() const { return actAbility; }

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
AirElemental::AirElemental(int owner)
    : Minion{"Air Elemental", owner, 0, 1, 1} {}

EarthElemental::EarthElemental(int owner)
    : Minion{"Earth Elemental", owner, 3, 4, 4} {}



