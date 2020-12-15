#include "spell.h"

Spell::Spell(std::string description) : description{description} {}

std::string Spell::getDescription(){ return description; }

void Spell::effect(std::shared_ptr<Game> game) {}
void Spell::effectWithTarget(std::shared_ptr<Game> game, int player, int target) {}
void Spell::effectWithTarget(std::shared_ptr<Game> game, int player, char ritual) {}

Spell::~Spell(){}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
