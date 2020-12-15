#include "board.h"
#include "../cards/minion/minion.h"
#include "../cards/minion/enchantment.h"

using namespace std;

bool Board::isFull() const{
    return (minions.size()==BOARD_CAP);
}

// Add card to hand, called by draw() in Player
bool Board::addMinionRight(shared_ptr<Minion> minion){
    if (isFull()){ 
        return false;
    }
    minions.push_back(minion);
    return true;
}

shared_ptr<Ritual> Board::getRitual() const{
    return ritual;
}

void Board::setRitual(shared_ptr<Ritual> ritual) {
    this->ritual = ritual;
}

shared_ptr<Minion> Board::getMinion(int minion) const {
    if(minions.size() - 1 < minion){
        // then there aren't as many cards as requested index, throw error
    }
    return minions[minion];
}

void Board::setMinion(int minion, shared_ptr<Minion> newMinion) {
    if(minions.size() - 1 < minion){
        // then there aren't as many cards as requested index, throw error
    }
    minions[minion] = newMinion;
}

shared_ptr<Minion> Board::removeMinion(int minion) {
    if(minions.size() - 1 < minion){
        // then there aren't as many cards as requested index, throw error
    }
    auto tmp = minions[minion];
    minions.erase(minions.begin()+minion);
    return tmp;
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
        while(minion->getName().compare("Delay") == 0){
            std::shared_ptr<Delay> delay  = std::static_pointer_cast<Delay>(minion);
            if(delay->getRound() == 1){
                minion = delay->getComponent();
                minion->setAtk(minion->getAtk() + delay->getAtk());
                minion->setDef(minion->getDef() + delay->getDef());
            } else{
                break;
            }
        }
    }

}

void Board::printBoard() {
    for (auto card : minions){
        cout << card->getName() << endl;
    }
}

