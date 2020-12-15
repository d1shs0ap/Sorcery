#include "graveyard.h"
#include "../cards/minion/minion.h"
#include "../argException.h"

using namespace std;

Graveyard::Graveyard() {
    // initialize minion vector
    minions = {};
}


bool Graveyard::isEmpty(){
    return minions.empty();
}

shared_ptr<Minion> Graveyard::getMinionTop() {
    if (isEmpty()){
        throw ArgException{"Top minion cannot be retrieved from graveyard because graveyard is empty."};
    }
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