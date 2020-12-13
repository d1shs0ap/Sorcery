#include "triggeredAbility.h"

#include "../../game/game.h"
#include "../../game/player.h"
#include "minion.h"
#include "../../cardCollections/board.h"
#include "../ritual.h"


TriggeredAbility::TriggeredAbility(std::string description, TriggeredAbilityType type)
    : description{description}, type{type} {}

TriggeredAbility::TriggeredAbility() {}

std::string TriggeredAbility::getDescription() const { return description; }

TriggeredAbilityType TriggeredAbility::getType() const { return type; }

DieDamage::DieDamage()
    : TriggeredAbility{"Deals damage to all the opponent minions equal to its attack value when it dies",
                       TriggeredAbilityType::MINION_DEATH} {}


void DieDamage::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const
{
    int opp = (minion->getOwner() + 1) % 2;
    int atk = minion->getAtk();
    for (int i = 0; i < 5; i++)
    {
        std::shared_ptr<Minion> oppMinion = game->getPlayer(opp)->getBoard()->getMinion(i);
        if (oppMinion != nullptr)
        {
            oppMinion->setDef(oppMinion->getDef() - atk);
        }
    }
}

EnterDamage::EnterDamage()
    : TriggeredAbility{"Whenever an opponent's minion enters play, deal 1 damage to it",
                       TriggeredAbilityType::ENEMY_MINION_ENTER} {}


void EnterDamage::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const
{
    int opp = (minion->getOwner() + 1) % 2;
    int len = game->getPlayer(opp)->getBoard()->getMinions().size();
    std::shared_ptr<Minion> target = game->getPlayer(opp)->getBoard()->getMinion(len - 1);
    target->setDef(target->getDef() - 1);
}

EndGainDef::EndGainDef()
    : TriggeredAbility{"At the end of your turn, all yout minions gain +0/+1",
                       TriggeredAbilityType::END_TURN} {}

void EndGainDef::effect(std::shared_ptr<Game> game, std::shared_ptr<Minion> minion) const
{
    std::shared_ptr<Player> owner = game->getPlayer(getMinion()->getOwner());
    int len = owner->getBoard()->getMinions().size();
    for (int i = 0; i < len; i++)
    {
        std::shared_ptr<Minion> target = owner->getBoard()->getMinion(i);
        target->setDef(target->getDef() + 1);
    }
}

StartGainMagic::StartGainMagic()
    : TriggeredAbility{"At the start of your turn, gain 1 magic",
                       TriggeredAbilityType::START_TURN} {}


void StartGainMagic::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const
{
    std::shared_ptr<Player> owner = game->getPlayer(ritual->Card::getOwner());
    owner->setMagic(owner->getMagic() + 1);
}

EnterGainAtkDef::EnterGainAtkDef()
    : TriggeredAbility{"Whenever a minion enters play under your control, it gains+1/+1",
                       TriggeredAbilityType::OWN_MINION_ENTER} {}


void EnterGainAtkDef::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> ritual) const
{
    int index = game->getPlayer(ritual->Card::getOwner())->getBoard()->getMinions().size() - 1;
    std::shared_ptr<Minion> target = game->getPlayer(ritual->Card::getOwner())->getBoard()->getMinion(index);
    target->setAtk(target->getAtk() + 1);
    target->setDef(target->getDef() + 1);
}

EnterDestroy::EnterDestroy()
    : TriggeredAbility{"Whenever a minion enters play, destroy it",
                       TriggeredAbilityType::MINION_ENTER} {}


void EnterDestroy::effect(std::shared_ptr<Game> game, std::shared_ptr<Ritual> minion) const {
    int index = game->getActivePlayer()->getBoard()->getMinions().size();
    std::shared_ptr<Minion> target = game->getActivePlayer()->getBoard()->getMinion(index);
    game->destroyMinion(target);
}
