#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "../cards/ritual.h"

class Board {
    std::vector<std::shared_ptr<Ritual>> ritual;
    std::vector<std::shared_ptr<Card>> minions;
};

#endif
