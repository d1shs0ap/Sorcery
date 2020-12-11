#include "activatedAbility.h"

ActivatedAbility::ActivatedAbility(){}

ActivatedAbility::ActivatedAbility(std::string description, int cost)
    : description{description}, cost{cost} {}

int ActivatedAbility::getCost() const { return cost; }

std::string ActivatedAbility::getDescription() const { return description; }



