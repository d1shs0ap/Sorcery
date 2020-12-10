#include "triggeredAbility.h"

TriggeredAbility::TriggeredAbility(std::string description, int type, int owner, std::shared_ptr<Minion> minion)
    : description{description}, type{type}, owner{owner}, minion{minion} {}

TriggeredAbility::TriggeredAbility() {}

std::string TriggeredAbility::getDescription() const { return description; }

int TriggeredAbility::getType() const { return type; }

int TriggeredAbility::getOwner() const { return owner; }

std::shared_ptr<Minion> TriggeredAbility::getMinion() const{ return minion; }

DieDamage::DieDamage(int owner, std::shared_ptr<Minion> minion) :
    TriggeredAbility{"Deals damage to all the opponent minions equal to its attack value when it dies", 4, owner, minion} {}

void DieDamage::effect(Game game) const {
    int opp = (TriggeredAbility::getOwner() + 1) % 2;
    int atk = TriggeredAbility::getMinion()->getAtk();
    for(int i = 0; i < 5; i++){
        std::shared_ptr<Minion> oppMinion = game.getPlayer(opp)->getBoard()->getMinion(i);
        if(oppMinion != nullptr){
            oppMinion->setDef(oppMinion->getDef() - atk);
        }
    }
}
