#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>
#include <map>

const int BOARD_CAP = 5;

class Ritual;
class Minion;

class Board {
    std::shared_ptr<Ritual> ritual;
    std::vector<std::shared_ptr<Minion>> minions;

    std::map<int, int> subTypeCount;
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

        // return the number of minion in board that is type
        int checkMinionSubType(int type) const;

        // When there are more than or equal to 3 ELEMENTAL on board each one +1/+1
        // when there are more than or equal to 2 SUMMONER on board each one +0/*2
        void MinionSubTypeEffect();



        // for testing
        void printBoard();
};

#endif
