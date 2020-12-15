#include "spell.h"
#include "card.h"
#include "ritual.h"
#include "minion/minion.h"
#include "minion/enchantment.h"
#include "../game/game.h"
#include "../game/player.h"
#include "../cardCollections/board.h"
#include "../cardCollections/hand.h"
#include "../cardCollections/graveyard.h"
#include "../argException.h"

Spell::Spell(std::string name, int owner, int cost, std::string description) :
    Card{name, "Spell", owner, cost}, description{description} {}

std::string Spell::getDescription() const{ return description; }

void Spell::effect(std::shared_ptr<Game> game) { }

void Spell::effectWithTarget(std::shared_ptr<Game> game, int player, int target) { }

void Spell::effectWithTarget(std::shared_ptr<Game> game, int player) { }

Spell::~Spell(){}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Banish::Banish(int owner) : Spell{"Banish", owner, 2, "Destroy target minion or ritual"} {}

void Banish::effect(std::shared_ptr<Game> game){
    std::string message = getName() + " needs a target";
    throw ArgException{message};
}

void Banish::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
    game->destroyMinion(game->getPlayer(player), target);
}

void Banish::effectWithTarget(std::shared_ptr<Game> game, int player){
    game->getPlayer(player)->getBoard()->setRitual(nullptr);
}
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Unsummon::Unsummon(int owner) : Spell{"Unsummon", owner, 1, "Return target minion to its owner's hand"} {}

void Unsummon::effect(std::shared_ptr<Game> game){
    std::string message = getName() + " needs a target minion";
    throw ArgException{message};
}

void Unsummon::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
    if(game->getPlayer(player)->getHand()->isFull()){
        game->getPlayer(player)->getBoard()->removeMinion(target);
    } else{
        game->getPlayer(player)->getHand()->addCardRight(game->getPlayer(player)->getBoard()->removeMinion(target)->getAttachedMinion());
    }
}

void Unsummon::effectWithTarget(std::shared_ptr<Game> game, int player){
    std::string message = getName() + " needs a target minion";
    throw ArgException{message};
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Recharge::Recharge(int owner) : Spell{"Recharge", owner, 1, "Your ritual gains 3 charges"} {}

void Recharge::effect(std::shared_ptr<Game> game){
    std::string message = getName() + " needs a target ritual";
    throw ArgException{message};
}

void Recharge::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
    std::string message = getName() + " needs a target ritual";
    throw ArgException{message};
}

void Recharge::effectWithTarget(std::shared_ptr<Game> game, int player){
    std::shared_ptr<Ritual> target = game->getPlayer(player)->getBoard()->getRitual();
    if(target == nullptr){
        std::string message = "Target ritual cannot be empty";
        throw ArgException{message};
    } else{
        target->setCharges(target->getCharges() + 3);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Disenchant::Disenchant(int owner) : Spell{"Disenchant", owner, 1, "Destroy the top enchantment on target minion"} {}

void Disenchant::effect(std::shared_ptr<Game> game){
    std::string message = getName() + " needs a target minion";
    throw ArgException{message};
}

void Disenchant::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
    std::shared_ptr<Minion> targetMinion = game->getPlayer(player)->getBoard()->getMinion(target);
    if(targetMinion->getType().compare("Enchantment") == 0){
        std::shared_ptr<Enchantment> targetEnchantment = std::static_pointer_cast<Enchantment>(targetMinion);
        targetMinion = targetEnchantment->detach();
    }
}

void Disenchant::effectWithTarget(std::shared_ptr<Game> game, int player){
    std::string message = getName() + " needs a target minion";
    throw ArgException{message};

}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

RaiseDead::RaiseDead(int owner) : Spell{"Raise Dead", owner, 1, "Resurrect the top minion in your graveyard and set its defence to 1"} {}

void RaiseDead::effect(std::shared_ptr<Game> game){
    if(game->getActivePlayer()->getGraveyard()->isEmpty()){
        std::string message = "Target graveyard cannot be empty";
        throw ArgException{message};
    } else{
        if(!(game->getActivePlayer()->getBoard()->isFull())){
            game->getActivePlayer()->getBoard()->addMinionRight(game->getActivePlayer()->getGraveyard()->getMinionTop());
        }
    }
}

void RaiseDead::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
    std::string message = getName() + " does not need a target";
    throw ArgException{message};

}

void RaiseDead::effectWithTarget(std::shared_ptr<Game> game, int player){
    std::string message = getName() + " does not need a target";
    throw ArgException{message};
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Blizzard::Blizzard(int owner) : Spell{"Blizzard", owner, 3, "Deal 2 damage to all minions"} {}

void Blizzard::effect(std::shared_ptr<Game> game){
    for(auto minion : game->getActivePlayer()->getBoard()->getMinions()){
        minion->setDef(minion->getDef() - 2);
    }
    for(auto minion : game->getInactivePlayer()->getBoard()->getMinions()){
        minion->setDef(minion->getDef() - 2);
    }
}

void Blizzard::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
    std::string message = getName() + " does not need a target";
    throw ArgException{message};
}

void Blizzard::effectWithTarget(std::shared_ptr<Game> game, int player){
    std::string message = getName() + " does not need a target";
    throw ArgException{message};
}
