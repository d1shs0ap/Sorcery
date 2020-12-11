#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <iostream>
#include <memory>

#include "observer.h"

class TextDisplay : public Observer {
    std::vector<std::vector<char>> display;
    public:
        virtual void update(Subject & game) override;
        // displays all help commands
        void printHelp();
        // displays minion as well as all of the enchantments on it of the active player
        void printMinion(std::shared_ptr<Player> activePlayer, int minion);
        // display active player's hand
        void printHand(std::shared_ptr<Player> activePlayer);
        // displays board, where the active player's content is displayed on the bottom
        void printBoard(std::shared_ptr<Player> activePlayer);
};

#endif
