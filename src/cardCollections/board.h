#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "../cards/ritual.h"
#include "../cards/minion/minion.h"

class Board {
    std::shared_ptr<Ritual> ritual;
    std::vector<std::shared_ptr<Minion>> minions;
    public:
        std::shared_ptr<Ritual> getRitual() const;
        void setRitual(std::shared_ptr<Ritual> ritual);

        std::vector<std::shared_ptr<Minion>> getMinions() const;
        void setMinions(std::vector<std::shared_ptr<Minion>> minions);
        
        // Calls all restoreActions() on player's minions
        void restoreActionAll();
};

#endif
