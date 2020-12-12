#include "ritual.h"

using namespace std;

Ritual::Ritual(string name, int owner, int cost, int activationCost, int charges) 
    : Card{name, "Ritual", owner, cost},
    activationCost{activationCost}, charges{charges} {}

TriggeredAbility Ritual::getTrgAbility() const {
    return trgAbility;
}

void Ritual::setTrgAbility(TriggeredAbility ability){
    trgAbility = ability;
}

bool Ritual::useTrgAbility(shared_ptr<Game> game) {
    if(charges - activationCost < 0) {
        return false;
    }
    charges -= activationCost;
    trgAbility.effect(game);
    return true;
}

DarkRitual::DarkRitual(int owner)
    : Ritual{"Dark Ritual", owner, 0, 1, 5} {
        Ritual::setTrgAbility(StartGainMagic{shared_from_this());
    }

AuraOfPower::AuraOfPower(int owner)
    : Ritual{"Aura of Power", owner, 1, 1, 4, EnterGainAtkDef{shared_from_this()}} {}

Standstill::Standstill(int owner)
    : Ritual{"Standstill", owner, 3, 2, 4, EnterDestroy{shared_from_this()}} {}