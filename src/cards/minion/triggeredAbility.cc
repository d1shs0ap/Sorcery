#include "triggeredAbility.h"

TriggeredAbility::TriggeredAbility(std::string description, int type)
    : description{description}, type{type} {}

TriggeredAbility::TriggeredAbility() {}

std::string TriggeredAbility::getDescription() { return description; }

int TriggeredAbility::getType() { return type; }