#include "board.h"

using namespace std;

shared_ptr<Ritual> Board::getRitual() const{
    return ritual;
}
void Board::setRitual(shared_ptr<Ritual> ritual) {
    this->ritual = ritual;
}

vector<shared_ptr<Minion>> Board::getMinions() const{
    return minions;
}
void Board::setMinions(vector<shared_ptr<Minion>> minions) {
    this->minions = minions;
}

// Calls all restoreActions() on minions on board
void Board::restoreActionAll(){
    for (auto minion : minions) {
        minion->restoreAction();
    }
}
