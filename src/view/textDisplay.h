#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <iostream>
#include <memory>

#include "../game/game.h"

class Player;
class TextDisplay {
    const string horizontalBoard;
    const string emptyLine;   
    const string numberBorder;
    std::shared_ptr<Game> game;
    // convert a card to appropriate strings.
    std::vector<string> cardVector(Card &card);
    //void TextDisplay::printHelp();
    void TextDisplay::addSpace(string &s, int n);
    public:
        // virtual void update(Subject & game) override;
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
