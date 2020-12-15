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

void Spell::effect(std::shared_ptr<Game> game) {}
void Spell::effectWithTarget(std::shared_ptr<Game> game, int player, int target) {}
void Spell::effectWithTarget(std::shared_ptr<Game> game, int player) {}

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

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Unsummon::Unsummon(int owner) : Spell{"Unsummon", owner, 1, "Return target minion to its owner's hand"} {}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Recharge::Recharge(int owner) : Spell{"Recharge", owner, 1, "Your ritual gains 3 charges"} {}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Disenchant::Disenchant(int owner) : Spell{"Disenchant", owner, 1, "Destroy the top enchantment on target minion"} {}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

RaiseDead::RaiseDead(int owner) : Spell{"Raise Dead", owner, 1, "Resurrect the top minion in your graveyard and set its defence to 1"} {}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

Blizzard::Blizzard(int owner) : Spell{"Blizzard", owner, 3, "Deal 2 damage to all minions"} {}
