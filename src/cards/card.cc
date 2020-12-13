#include "card.h"

Card::Card() {}
Card::Card(std::string name, std::string type, int owner, int cost)
    : name{name}, type{type}, owner{owner}, cost{cost} {}

int Card::getCost() const { return cost; }
int Card::getOwner() const { return owner; }
std::string Card::getName() const { return name; }
std::string Card::getType() const { return type; }
