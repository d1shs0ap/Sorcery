#include "ritual.h"

using namespace std;

Ritual::Ritual(int activationCost, int charges, TriggeredAbility trgAbility) 
    : activationCost{activationCost}, charges{charges}, trgAbility{trgAbility} {}

TriggeredAbility Ritual::getTrgAbility() const {
    return trgAbility;
}

bool Ritual::useTrgAbility(shared_ptr<Game> game) {
    if(charges - activationCost < 0) {
        return false;
    }
    charges -= activationCost;
    trgAbility.effect(game);
    return true;
}
