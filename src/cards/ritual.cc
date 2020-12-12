#include "ritual.h"

using namespace std;

Ritual::Ritual(int activationCost, int charges, TriggeredAbility trgAbility) 
    : activationCost{activationCost}, charges{charges}, trgAbility{trgAbility} {}

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
    : Ritual{"Fire Elemental", owner, 2, 2, 2} {
        Minion::setTrgAbility(EnterDamage(make_shared<Minion>(this)));
    }

FireElemental::FireElemental(int owner)
    : Minion{"Fire Elemental", owner, 2, 2, 2} {
        Minion::setTrgAbility(EnterDamage(std::make_shared<Minion>(this)));
    }