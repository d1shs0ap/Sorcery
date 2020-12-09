#include "card.h"

Card::Card(std::string name, std::string type, int owner, int cost) : 
    name{name},
    type{type},
    owner{owner},
    cost{cost} {

    }
Card::Card(){}

int Card::getCost(){ return cost;}

int Card::getOwner(){ return owner;}

std::string Card::getName(){ return name;}

std::string Card::getType(){ return type;}