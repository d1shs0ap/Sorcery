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
        // Default constructor
        Board();
        // Check if minions.size() >= BOARD_CAP
        bool isFull() const;
        // Add minion to minions if minions id not full
        void addMinionRight(std::shared_ptr<Minion> minion);

        // Getter and Setter
        std::shared_ptr<Ritual> getRitual() const;
        void setRitual(std::shared_ptr<Ritual> ritual);
        // Get the Minion that is in minions at the position minion
        std::shared_ptr<Minion> getMinion(int minion) const;
        // Set minions[minion] to newMinion
        void setMinion(int minion, std::shared_ptr<Minion> newMinion);

        // Remove minions[minion] from minions, called by Game::detroyMinion
        std::shared_ptr<Minion> removeMinion(int minion);
        // Return the index of target in minions, if not found return -1
        int findMinion(std::shared_ptr<Minion> target) const;

        // Getter and Setter
        std::vector<std::shared_ptr<Minion>> getMinions() const;
        void setMinions(std::vector<std::shared_ptr<Minion>> minions);
        
        // Calls all restoreActions() on player's minions
        void restoreActionAll();



        // for testing
        void printBoard();
};

#endif
