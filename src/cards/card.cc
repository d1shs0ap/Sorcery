#include "card.h"

Card::Card(std::string name, std::string type, int owner, int cost) : 
    name{name},
    type{type},
    owner{owner},
    cost{cost} {
        
    }

