#include "triggeredAbility.h"

TriggeredAbility::TriggeredAbility(std::string description, int type, std::shared_ptr<Minion> minion)
    : description{description}, type{type}, minion{minion} {}

TriggeredAbility::TriggeredAbility() {}

std::string TriggeredAbility::getDescription() const { return description; }

int TriggeredAbility::getType() const { return type; }

std::shared_ptr<Minion> TriggeredAbility::getMinion() const{ return minion; }

DieDamage::DieDamage(std::shared_ptr<Minion> minion) :
    TriggeredAbility{"Deals damage to all the opponent minions equal to its attack value when it dies", 4, minion} {}

void DieDamage::effect(Game game) const {
    int opp = (TriggeredAbility::getMinion()->getOwner() + 1) % 2;
    int atk = TriggeredAbility::getMinion()->getAtk();
    for(int i = 0; i < 5; i++){
        std::shared_ptr<Minion> oppMinion = game.getPlayer(opp)->getBoard()->getMinion(i);
        if(oppMinion != nullptr){
            oppMinion->setDef(oppMinion->getDef() - atk);
        }
    }
}

EnterDamage::EnterDamage(std::shared_ptr<Minion> minion) : 
    TriggeredAbility{"Whenever an opponent's minion enters play, deal 1 damage to it", 5, minion} {}

void EnterDamage::effect(Game game) const {
    int opp = (TriggeredAbility::getMinion()->getOwner() + 1) % 2;
    int len = game.getPlayer(opp)->getBoard()->getMinions().size();
    std::shared_ptr target = game.getPlayer(opp)->getBoard()->getMinion(len - 1);
    target->setDef(target->getDef() - 1);
}

EndGainDef::EndGainDef(std::shared_ptr<Minion> minion) : 
    TriggeredAbility{"At the end of your turn, all yout minions gain +0/+1", 2, minion} {}


void EndGainDef::effect(Game game) const {
    std::shared_ptr<Player> owner = game.getPlayer(TriggeredAbility::getMinion()->getOwner());
    int len = owner->getBoard()->getMinions().size();
    for (int i = 0; i < len; i++){
        std::shared_ptr target = owner->getBoard()->getMinion(i);
        target->setDef(target->getDef() + 1);
    }
}