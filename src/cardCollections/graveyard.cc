#include "graveyard.h"
#include "../cards/minion/minion.h"

using namespace std;

shared_ptr<Minion> Graveyard::getMinionTop() const {
    return minions.back();
}
// Add new minion to graveyard top
void Graveyard::addMinionTop(shared_ptr<Minion> minion) {
    minions.push_back(minion);
}

// Accessor and mutator for minions
vector<shared_ptr<Minion>> Graveyard::getMinions() const {
    return minions;
}
void Graveyard::setMinions(vector<shared_ptr<Minion>> minions) {
    this->minions = minions;
}