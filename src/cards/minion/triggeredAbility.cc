#include "triggeredAbility.h"

TriggeredAbility::TriggeredAbility(std::string description, TriggeredAbilityType type)
    : description{description}, type{type} {}

TriggeredAbility::TriggeredAbility() {}

std::string TriggeredAbility::getDescription() const { return description; }

TriggeredAbilityType TriggeredAbility::getType() const { return type; }


DieDamage::DieDamage(std::shared_ptr<Minion> minion) :
    TriggeredAbility{"Deals damage to all the opponent minions equal to its attack value when it dies", 
    TriggeredAbilityType::MINION_DEATH}, 
    minion{minion} {}

std::shared_ptr<Minion> DieDamage::getMinion() const { return minion; }

void DieDamage::effect(std::shared_ptr<Game> game) const {
    int opp = (getMinion()->getOwner() + 1) % 2;
    int atk = getMinion()->getAtk();
    for(int i = 0; i < 5; i++){
        std::shared_ptr<Minion> oppMinion = game->getPlayer(opp)->getBoard()->getMinion(i);
        if(oppMinion != nullptr){
            oppMinion->setDef(oppMinion->getDef() - atk);
        }
    }
}

EnterDamage::EnterDamage(std::shared_ptr<Minion> minion) : 
    TriggeredAbility{"Whenever an opponent's minion enters play, deal 1 damage to it", 
    TriggeredAbilityType::ENEMY_MINION_ENTER},
    minion{minion} {}

std::shared_ptr<Minion> EnterDamage::getMinion() const { return minion; }

void EnterDamage::effect(std::shared_ptr<Game> game) const {
    int opp = (getMinion()->getOwner() + 1) % 2;
    int len = game->getPlayer(opp)->getBoard()->getMinions().size();
    std::shared_ptr target = game->getPlayer(opp)->getBoard()->getMinion(len - 1);
    target->setDef(target->getDef() - 1);
}

EndGainDef::EndGainDef(std::shared_ptr<Minion> minion) : 
    TriggeredAbility{"At the end of your turn, all yout minions gain +0/+1",
    TriggeredAbilityType::END_TURN}, 
    minion{minion} {}

std::shared_ptr<Minion> EndGainDef::getMinion() const { return minion; }


void EndGainDef::effect(std::shared_ptr<Game> game) const {
    std::shared_ptr<Player> owner = game->getPlayer(getMinion()->getOwner());
    int len = owner->getBoard()->getMinions().size();
    for (int i = 0; i < len; i++){
        std::shared_ptr target = owner->getBoard()->getMinion(i);
        target->setDef(target->getDef() + 1);
    }
}