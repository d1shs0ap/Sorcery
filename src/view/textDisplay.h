#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <iostream>
#include <memory>

#include "../game/game.h"

class Player;
class TextDisplay { 
    const string horizontalLine     {"|-------------------------------|"};
    const string numberBorderLine   {"|------                   ------|"};
    const string nameLine           {"|                         |     |"};
    const string emptyLine          {"|                               |"};

    std::shared_ptr<Game> game;

    // convert a card to appropriate strings.
    void addSpace(std::string &s, int n);

    // print a card template
    std::vector<std::string> printCardTemplate();
    // print enchantment when it is on board, attached to minions
    std::vector<std::string> printEnchantedMinion(std::shared_ptr<Enchantment> enchantment);
    // print enchantment when it is in hand
    std::vector<std::string> printEnchantment(std::shared_ptr<Enchantment> enchantment);
    // print minion
    std::vector<std::string> printMinion(std::shared_ptr<Minion> minion);
    // print spell
    std::vector<std::string> printSpell(std::shared_ptr<Spell> spell);
    // print ritual
    std::vector<std::string> printRitual(std::shared_ptr<Ritual> ritual);

    public:
        // virtual void update(Subject & game) override;
        // displays all help commands
        void printHelp();
        // displays minion as well as all of the enchantments on it of the active player, called by inspect
        void printInspect(std::shared_ptr<Player> activePlayer, int minion);
        // display active player's hand, called by hand
        void printHand(std::shared_ptr<Player> activePlayer);
        // displays board, where the active player's content is displayed on the bottom, called by board
        void printBoard(std::shared_ptr<Player> activePlayer);
};

#endif
