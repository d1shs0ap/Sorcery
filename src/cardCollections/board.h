#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

const int BOARD_CAP = 5;

class Ritual;
class Minion;

class Board {
    std::shared_ptr<Ritual> ritual;
    std::vector<std::shared_ptr<Minion>> minions;
    public:
        bool isFull() const;

        bool addMinionRight(std::shared_ptr<Minion> minion);

        std::shared_ptr<Ritual> getRitual() const;
        void setRitual(std::shared_ptr<Ritual> ritual);

        std::shared_ptr<Minion> getMinion(int minion) const;
        std::shared_ptr<Minion> removeMinion(int minion);

        std::vector<std::shared_ptr<Minion>> getMinions() const;
        void setMinions(std::vector<std::shared_ptr<Minion>> minions);
        
        // Calls all restoreActions() on player's minions
        void restoreActionAll();
};

#endif
