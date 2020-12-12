#include "ritual.h"

using namespace std;

Ritual::Ritual() {
    
}
TriggeredAbility Ritual::getTrgAbility() const {
    return trgAbility;
}

bool Ritual::useTrgAbility() {
    if(charges - activationCost < 0) {
        return false;
    }
    charges -= activationCost;

}
