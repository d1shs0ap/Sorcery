#include "minion.h"

using namespace std;

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

void Minion::restoreAction() { actions = actionsCap; }
ActivatedAbility Minion::getActAbility() const { return actAbility; }
TriggeredAbility Minion::getTrgAbility() const { return trgAbility; }
void Minion::setActAbility(ActivatedAbility ability){
    actAbility = ability;
}

void Minion::setTrgAbility(TriggeredAbility ability){
    trgAbility = ability;
}

void Minion::attack(shared_ptr<Player> other)
{
    if (actions > 0)
    {
        int attack = this->computeAtk();
        other->setLife(other->getLife() - attack);
        --actions;
    }
}

void Minion::attack(shared_ptr<Minion> other)
{
    if (actions > 0)
    {
        other->setDef(other->getDef() - this->computeAtk());
        --actions;
    }
    this->setDef(this->getDef() - other->computeAtk());
}

void Minion::useAbility()
{
}

std::string Minion::digitDisplay() const{
    std::string digitLine;
    digitLine += "| ";
    digitLine += std::to_string(atk);
    for(int i = digitLine.length(); i < 7; i++){
        digitLine += " ";
    }
    digitLine += "|";
    for(int i = 0; i < 19; i++){
        digitLine += " ";
    }
    digitLine += "|";
    std::string defStr = std::to_string(def);
    for(int i = 0; i < 4 - defStr.length(); i++){
        digitLine += " ";
    }
    digitLine += defStr;
    digitLine += " |";
    return digitLine;

}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
AirElemental::AirElemental(int owner)
    : Minion{"Air Elemental", owner, 0, 1, 1} {}

EarthElemental::EarthElemental(int owner)
    : Minion{"Earth Elemental", owner, 3, 4, 4} {}

Bomb::Bomb(int owner)
    : Minion{"Bomb", owner, 2, 1, 2} { 
        Minion::setTrgAbility(DieDamage(std::make_shared<Minion>(this)));
    }

FireElemental::FireElemental(int owner)
    : Minion{"Fire Elemental", owner, 2, 2, 2} {
        Minion::setTrgAbility(EnterDamage(std::make_shared<Minion>(this)));
    }

PotionSeller::PotionSeller(int owner)
    : Minion{"Potion Seller", owner, 2, 1, 3} {
        Minion::setTrgAbility(EndGainDef(std::make_shared<Minion>(this)));
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






