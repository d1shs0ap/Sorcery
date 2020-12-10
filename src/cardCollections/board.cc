#include "board.h"

using namespace std;

shared_ptr<Ritual> Board::getRitual() {
    return ritual;
}
void Board::setRitual(shared_ptr<Ritual> ritual) {
    this->ritual = ritual;
}

vector<shared_ptr<Card>> Board::getMinions() {
    return minions;
}
void Board::setMinions(vector<shared_ptr<Card>> minions) {
    this->minions = minions;
}