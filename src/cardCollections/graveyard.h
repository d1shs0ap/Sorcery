#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include <memory>
#include <vector>


class Minion;

class Graveyard {
    // minions from bottom to top
    std::vector<std::shared_ptr<Minion>> minions;
    public:
        Graveyard();

        // Check if minions is empty
        bool isEmpty();

        // Get the top minion in graveyard
        std::shared_ptr<Minion> getMinionTop();
        // Add new minion to graveyard top
        void addMinionTop(std::shared_ptr<Minion> minion);
        // remove the top minion in graveyard and return it
        std::shared_ptr<Minion> removeMinionTop();

        // Accessor and mutator for minions
        std::vector<std::shared_ptr<Minion>> getMinions() const;
        void setMinions(std::vector<std::shared_ptr<Minion>> minions);

        void printGraveyard();
        
};

#endif
