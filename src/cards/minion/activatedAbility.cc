#include "activatedAbility.h"
#include "minion.h"

ActivatedAbility::ActivatedAbility() {}

ActivatedAbility::ActivatedAbility(std::string description, int cost, std::shared_ptr<Minion> minion)
    : description{description}, cost{cost} {}

int ActivatedAbility::getCost() const { return cost; }

std::string ActivatedAbility::getDescription() const { return description; }


