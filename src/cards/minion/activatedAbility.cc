#include "activatedAbility.h"

ActivatedAbility::ActivatedAbility(){}

ActivatedAbility::ActivatedAbility(std::string description, int cost)
    : description{description}, cost{cost} {}

int ActivatedAbility::getCost(){ return cost; }

std::string ActivatedAbility::getDescription(){ return description; }

