#include "triggeredAbility.h"

#include "../../game/game.h"
#include "../../game/player.h"
#include "minion.h"
#include "../../cardCollections/board.h"
#include "../ritual.h"
#include "../../argException.h"


TriggeredAbility::TriggeredAbility(std::string description, TriggeredAbilityType type)
    : description{description}, type{type} {}

TriggeredAbility::TriggeredAbility() {}

std::string TriggeredAbility::getDescription() const { return description; }

TriggeredAbilityType TriggeredAbility::getType() const { return type; }

void TriggeredAbility::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const{

}
void TriggeredAbility::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const{

}

TriggeredAbility::~TriggeredAbility() {}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DieDamage ////////////////////////////////////////////////////////////////////////////////////////////////////////

DieDamage::DieDamage()
    : TriggeredAbility{"Deals damage to all the opponent minions equal to its attack value when it dies",
                       TriggeredAbilityType::MINION_DEATH} {}

void DieDamage::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const
{
    int opp = (minion->getOwner() + 1) % 2;
    int atk = minion->getAtk();
    for(auto oppMinion : game->getPlayer(opp)->getBoard()->getMinions()){
        oppMinion->setDef(oppMinion->getDef() - atk);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EnterDamage ////////////////////////////////////////////////////////////////////////////////////////////////////////

EnterDamage::EnterDamage()
    : TriggeredAbility{"Whenever an opponent's minionenters play, deal 1 damage toit",
                       TriggeredAbilityType::ENEMY_MINION_ENTER} {}


void EnterDamage::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const
{
    int opp = (minion->getOwner() + 1) % 2;
    int len = game->getPlayer(opp)->getBoard()->getMinions().size();
    std::shared_ptr<Minion> target = game->getPlayer(opp)->getBoard()->getMinion(len - 1);
    target->setDef(target->getDef() - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EndGainDef ////////////////////////////////////////////////////////////////////////////////////////////////////////

EndGainDef::EndGainDef()
    : TriggeredAbility{"At the end of your turn, all your minions gain +0/+1",
                       TriggeredAbilityType::END_TURN} {}

void EndGainDef::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const
{
    std::shared_ptr<Player> owner = game->getPlayer(minion->getOwner());
    for(auto minion : owner->getBoard()->getMinions()){
        minion->setDef(minion->getDef() + 1);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// StartGainMagic ////////////////////////////////////////////////////////////////////////////////////////////////////////

StartGainMagic::StartGainMagic()
    : TriggeredAbility{"At the start of your turn, gain 1 magic",
                       TriggeredAbilityType::START_TURN} {}


void StartGainMagic::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const
{
    std::shared_ptr<Player> owner = game->getPlayer(ritual->Card::getOwner());
    owner->setMagic(owner->getMagic() + 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EnterGainAtkDef ////////////////////////////////////////////////////////////////////////////////////////////////////////

EnterGainAtkDef::EnterGainAtkDef()
    : TriggeredAbility{"Whenever a minion enters play under your control, it gains +1/+1",
                       TriggeredAbilityType::OWN_MINION_ENTER} {}


void EnterGainAtkDef::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const {
    int index = game->getPlayer(ritual->Card::getOwner())->getBoard()->getMinions().size() - 1;
    std::shared_ptr<Minion> target = game->getPlayer(ritual->Card::getOwner())->getBoard()->getMinion(index);
    target->setAtk(target->getAtk() + 1);
    target->setDef(target->getDef() + 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EnterDestroy ////////////////////////////////////////////////////////////////////////////////////////////////////////

EnterDestroy::EnterDestroy()
    : TriggeredAbility{"Whenever a minion enters play, destroy it",
                       TriggeredAbilityType::MINION_ENTER} {}


void EnterDestroy::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> minion) const {
    int minionIndex = game->getActivePlayer()->getBoard()->getMinions().size();
    game->destroyMinion(game->getActivePlayer(), minionIndex - 1);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// EndDestroy ////////////////////////////////////////////////////////////////////////////////////////////////////////

EndDestroy::EndDestroy()
    : TriggeredAbility{"At the end of each turn, move all minions with attack 1 or less to the graveyard",
                       TriggeredAbilityType::END_TURN} {}


void EndDestroy::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const {

    int counter = 0;

    auto player = game->getPlayer(0);
    auto playerMinions = player->getBoard()->getMinions();

    try {
        // loop through all minions and check which has attack <= 1, keep track of them
        while (counter < playerMinions.size()){
            if(player->getBoard()->getMinion(counter)->getAtk() <= 1) {
                player->getBoard()->removeMinion(counter);
            } else {
                ++counter;
            }
        }
    } catch (ArgException &e) {}

    counter = 0;

    // now the same for the enemy
    auto enemy = game->getPlayer(1);
    auto enemyMinions = enemy->getBoard()->getMinions();

    try {
        while (counter < enemyMinions.size()){
            if(enemy->getBoard()->getMinion(counter)->getAtk() <= 1) {
                enemy->getBoard()->removeMinion(counter);
            } else {
                ++counter;
            }
        }
    } catch (ArgException &e) {}
}
