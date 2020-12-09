#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include <memory>
#include <vector>

#include "../cards/minion/minion.h"

class Graveyard {
    std::vector<std::shared_ptr<Minion>> minions;
    public:
        std::shared_ptr<Minion> getMinionTop();
        // Add new minion to graveyard top
        void addMinionTop();

        std::vector<std::shared_ptr<Minion>> getMinions();
        void setMinions();
        
};

#endif
