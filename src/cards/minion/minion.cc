#include "minion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Minion::Minion(std::string name, int owner, int cost, int atk, int def) : 
    Card{name, "Minion", owner, cost}, atk{atk}, def{def} {}
Minion::Minion() {}

int Minion::getAtk() const { return atk; }
int Minion::computeAtk() const { return getAtk(); }
void Minion::setAtk(int new_atk) { atk = new_atk; }
int Minion::getDef() const { return def; }
int Minion::computeDef() const { return getDef(); }
void Minion::setDef(int new_def) { def = new_def; }

void Minion::restoreActions() { actions = actionsCap; }
ActivatedAbility Minion::getActAbility() const { return actAbility; }
TriggeredAbility Minion::getTrgAbility() const { return trgAbility; }
void Minion::setActAbility(ActivatedAbility ability){
    actAbility = ability;
}

void Minion::setTrgAbility(TriggeredAbility ability){
    trgAbility = ability;
}

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

Bomb::Bomb(int owner)
    : Minion{"Bomb", owner, 2, 1, 2} {

    }

FireElemental::FireElemental(int owner)
    : Minion{"Fire Elemental", owner, 2, 2, 2} {

    }

PotionSeller::PotionSeller(int owner)
    : Minion{"Potion Seller", owner, 2, 1, 3} {

    }

NovicePyromancer::NovicePyromancer(int owner)
    : Minion{"Novice Pyromancer", owner, 1, 0, 1}{

    }

ApprenticeSummoner::ApprenticeSummoner(int owner)
    : Minion{"Apprentice Summoner", owner, 2, 1, 3}{

    }

MasterSummoner::MasterSummoner(int owner)
    : Minion{"Master Summoner", owner, 3, 2, 3}{

    }





