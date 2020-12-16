#include "graveyard.h"
#include "../cards/minion/minion.h"
#include "../argException.h"

using namespace std;

Graveyard::Graveyard() {}


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

std::shared_ptr<Minion> Graveyard::removeMinionTop(){
    auto top = getMinionTop();
    minions.erase(minions.begin() + minions.size() - 1);
    return top;
}


// Accessor and mutator for minions
vector<shared_ptr<Minion>> Graveyard::getMinions() const {
    return minions;
}
void Graveyard::setMinions(vector<shared_ptr<Minion>> minions) {
    this->minions = minions;
}

void Graveyard::printGraveyard() {
    cout << "Graveyard: "  << endl;
    for (auto minion: minions) {
        cout << minion->getName() << " "<< minion->getAtk() << " " << minion->getDef()<< endl;
    }
}
