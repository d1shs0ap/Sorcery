#include "spell.h"
#include "card.h"
#include "ritual.h"
#include "minion/minion.h"
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
    std::string message = getName() + "needs a target";
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
    std::string message = getName() + "needs a target minion";
    throw ArgException{message};
}

void Unsummon::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
    if(game->getPlayer(player)->getHand()->isFull());
}

void Unsummon::effectWithTarget(std::shared_ptr<Game> game, int player){
    std::string message = getName() + "needs a target minion";
    throw ArgException{message};
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Recharge::Recharge(int owner) : Spell{"Recharge", owner, 1, "Your ritual gains 3 charges"} {}

void Recharge::effect(std::shared_ptr<Game> game){
}

void Recharge::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
}

void Recharge::effectWithTarget(std::shared_ptr<Game> game, int player){

}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Disenchant::Disenchant(int owner) : Spell{"Disenchant", owner, 1, "Destroy the top enchantment on target minion"} {}

void Disenchant::effect(std::shared_ptr<Game> game){
}

void Disenchant::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
}

void Disenchant::effectWithTarget(std::shared_ptr<Game> game, int player){

}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

RaiseDead::RaiseDead(int owner) : Spell{"Raise Dead", owner, 1, "Resurrect the top minion in your graveyard and set its defence to 1"} {}

void RaiseDead::effect(std::shared_ptr<Game> game){
}

void RaiseDead::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
}

void RaiseDead::effectWithTarget(std::shared_ptr<Game> game, int player){

}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Blizzard::Blizzard(int owner) : Spell{"Blizzard", owner, 3, "Deal 2 damage to all minions"} {}

void Blizzard::effect(std::shared_ptr<Game> game){
}

void Blizzard::effectWithTarget(std::shared_ptr<Game> game, int player, int target){
}

void Blizzard::effectWithTarget(std::shared_ptr<Game> game, int player){

}
