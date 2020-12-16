#include "board.h"
#include "../cards/minion/minion.h"
#include "../cards/minion/enchantment.h"
#include "../argException.h"

using namespace std;

Board::Board() {
    subTypeCount[ELEMENTAL] = 0;
    subTypeCount[SUMMONER] = 0;
}

bool Board::isFull() const{
    return (minions.size()==BOARD_CAP);
}

// Add card to hand, called by draw() in Player
void Board::addMinionRight(shared_ptr<Minion> minion){
    if (isFull()){ 
        throw ArgException{minion->getName() +" cannot be added to board because board is full."};
    }
    minions.push_back(minion);
}

shared_ptr<Ritual> Board::getRitual() const{
    return ritual;
}

void Board::setRitual(shared_ptr<Ritual> ritual) {
    this->ritual = ritual;
}

shared_ptr<Minion> Board::getMinion(int minion) const {
    if(minions.size() <= minion){
        // then there aren't as many cards as requested index, throw error
        throw ArgException{"Minion " + to_string(minion + 1) + " cannot be retrieved from board because it does not exist."};
    }

    return minions[minion];
}

void Board::setMinion(int minion, shared_ptr<Minion> newMinion) {
    if(minions.size() <= minion){
        throw ArgException{"Minion " + to_string(minion + 1) + " cannot be changed on board because it does not exist."};
    }
    minions[minion] = newMinion;
}

shared_ptr<Minion> Board::removeMinion(int minion) {
    if(minions.size() <= minion){
        // then there aren't as many cards as requested index, throw error
        throw ArgException{"Minion"  + to_string(minion + 1) + " cannot be removed from board because it does not exist."};
    }
    auto tmp = minions[minion];
    minions.erase(minions.begin()+minion);
    return tmp;
}

int Board::findMinion(std::shared_ptr<Minion> target) const{
    for(int i = 0; i < minions.size(); i++){
        if(minions[i] == target) { return i; }
    }
    return -1;
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

int Board::checkMinionSubType(int type) const{
    int count = 0;
    MinionSubType enumType;
    if(type == ELEMENTAL) { enumType = ELEMENTAL; }
    else{ enumType = SUMMONER; }
    for(auto minion : minions){
        if(minion->isSubType(enumType)){ count++; }
    }
    return count;
}

void Board::MinionSubTypeEffect(){
    if(checkMinionSubType(ELEMENTAL) != subTypeCount[ELEMENTAL]){
        if(checkMinionSubType(ELEMENTAL) > subTypeCount[ELEMENTAL]){
            if(subTypeCount[ELEMENTAL] >= 3){
                int remain = checkMinionSubType(ELEMENTAL) - subTypeCount[ELEMENTAL];
                for(int i = minions.size() - 1; i >= 0; i--){
                    if(minions[i]->isSubType(ELEMENTAL)){
                        minions[i]->setAtk(minions[i]->getAtk() + 1);
                        minions[i]->setDef(minions[i]->getDef() + 1);
                        remain--;
                    }
                    if(remain == 0) { break; }
                }
            } else if(subTypeCount[ELEMENTAL] < 3 && checkMinionSubType(ELEMENTAL) >= 3){
                for(int i = 0; i< minions.size(); i++){
                    if(minions[i]->isSubType(ELEMENTAL)){
                        minions[i]->setAtk(minions[i]->getAtk() + 1);
                        minions[i]->setDef(minions[i]->getDef() + 1);
                    }
                }

            }
        } else if(checkMinionSubType(ELEMENTAL) < subTypeCount[ELEMENTAL]){
            if(checkMinionSubType(ELEMENTAL) < 3 && subTypeCount[ELEMENTAL] >= 3){
                for(int i = 0; i< minions.size(); i++){
                    if(minions[i]->isSubType(ELEMENTAL)){
                        minions[i]->setAtk(minions[i]->getAtk() - 1);
                        minions[i]->setDef(minions[i]->getDef() - 1);
                    }
                }
            }
        }
        subTypeCount[ELEMENTAL] = checkMinionSubType(ELEMENTAL);
    }
    if(checkMinionSubType(SUMMONER) != subTypeCount[SUMMONER]){
        if(checkMinionSubType(SUMMONER) > subTypeCount[SUMMONER]){
            if(subTypeCount[SUMMONER] >= 2){
                int remain = checkMinionSubType(SUMMONER) - subTypeCount[SUMMONER];
                for(int i = minions.size() - 1; i >= 0; i--){
                    if(minions[i]->isSubType(SUMMONER)){
                        minions[i]->setDef(minions[i]->getDef() * 2);
                        remain--;
                    }
                    if(remain == 0) { break; }
                }
            } else if(subTypeCount[SUMMONER] < 2 && checkMinionSubType(SUMMONER) >= 2){
                for(int i = 0; i< minions.size(); i++){
                    if(minions[i]->isSubType(SUMMONER)){
                        minions[i]->setDef(minions[i]->getDef() * 2);
                    }
                }

            }

        } else if(checkMinionSubType(SUMMONER) < subTypeCount[SUMMONER]){
            if(checkMinionSubType(SUMMONER) < 2 && subTypeCount[SUMMONER] >= 2){
                for(int i = 0; i< minions.size(); i++){
                    if(minions[i]->isSubType(SUMMONER)){
                        minions[i]->setDef(minions[i]->getDef() / 2);
                    }
                }
            }
        }

    }
    subTypeCount[SUMMONER] = checkMinionSubType(SUMMONER);
}

void Board::printBoard() {
    for (auto card : minions){
        cout << card->getName() << endl;
    }
}


