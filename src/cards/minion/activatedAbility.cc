#include "activatedAbility.h"
#include "minion.h"
#include "../../game/game.h"
#include "../card.h"
#include "../../game/player.h"
#include "../../cardCollections/board.h"
#include "../../argException.h"

////////////////////////////////////////////////////////////////////////////////////////
/// ActivatedAbility /////////////////////////////////////////////////////////////////

ActivatedAbility::ActivatedAbility() {}

ActivatedAbility::ActivatedAbility(std::string description, int cost)
    : description{description}, cost{cost} {}

int ActivatedAbility::getCost() const { return cost; }
void ActivatedAbility::setCost(int newCost) {cost = newCost; }

std::string ActivatedAbility::getDescription() const { return description; }

void ActivatedAbility::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const{}
void ActivatedAbility::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion,  std::shared_ptr<Minion> target) const{}

ActivatedAbility::~ActivatedAbility() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DamageTarget////////////////////////////////////////////////////////////////////////////////////////////////////////

DamageTarget::DamageTarget() : ActivatedAbility{"Deal 1 damage to target minion", 1} {}

void DamageTarget::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const {
    std::string message = minion->getName() + "'s activated ability needs a target.";
    throw ArgException{message};
}

void DamageTarget::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion, std::shared_ptr<Minion> target) const {
    target->setDef(target->getDef() - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// SummonOneAirElemental /////////////////////////////////////////////////////////////////////////////////////////////////

SummonOneAirElemental::SummonOneAirElemental() : ActivatedAbility{"Summon a 1/1 air elemental", 1} {}

void SummonOneAirElemental::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const{
    int owner = minion->getOwner();
    std::shared_ptr<Player> target = game->getPlayer(owner);
    if(target->getBoard()->getMinions().size() < 5){
        target->getBoard()->addMinionRight(std::make_shared<AirElemental>(owner));
    }
}

void SummonOneAirElemental::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion, std::shared_ptr<Minion> target) const{
    std::string message = minion->getName() + "'s activated ability does not need a target.";
    throw ArgException{message};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// SummonThreeAirElemental ///////////////////////////////////////////////////////////////////////////////////////////////

SummonThreeAirElemental::SummonThreeAirElemental() : ActivatedAbility{"Summon up to three 1/1 air elementals", 2} {}

void SummonThreeAirElemental::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const{
    int owner = minion->getOwner();
    std::shared_ptr<Player> target = game->getPlayer(owner);
    int remain = 3;
    while(target->getBoard()->getMinions().size() <= 5 && remain > 0){
        game->addMinion(owner, std::make_shared<AirElemental>(owner));
        remain--;
    }
}

void SummonThreeAirElemental::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion, std::shared_ptr<Minion> target) const{
    std::string message = minion->getName() + "'s activated ability does not need a target.";
    throw ArgException{message};
}
