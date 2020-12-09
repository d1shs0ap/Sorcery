#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "../cards/ritual.h"

class Board {
    std::shared_ptr<Ritual> ritual;
    std::vector<std::shared_ptr<Card>> minions;
    public:
        std::shared_ptr<Ritual> getRitual();
        void setRitual(std::shared_ptr<Ritual> ritual);

        std::vector<std::shared_ptr<Card>> getMinions();
        void setMinions(std::vector<std::shared_ptr<Card>> minions);
};

#endif
